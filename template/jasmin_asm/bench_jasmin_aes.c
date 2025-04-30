// gcc -std=c11 -O2 -Wall -maes -mssse3 -mavx bench_jasmin_aes.c jasmin_aes.S -o bench_jasmin_aes -lm
// ./bench_jasmin_aes > jasmin_results.csv


#define _POSIX_C_SOURCE 200809L
#ifdef __linux__
# define _GNU_SOURCE
# include <sched.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>
#include <math.h>
#include <smmintrin.h>
#include <immintrin.h>

// your Jasmin‐generated AES entrypoint in jasmin_aes.S
extern __m128i aes(__m128i key, __m128i block);

typedef uint8_t  u8;
typedef uint64_t u64;

/* rdtsc cycle counter */
static inline u64 rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((u64)hi << 32) | lo;
}

/* nanosecond diff */
static inline u64 diff_ns(const struct timespec *s, const struct timespec *e) {
    return (e->tv_sec - s->tv_sec) * 1000000000ULL + (e->tv_nsec - s->tv_nsec);
}

/* stats helpers */
static double mean(const double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += v[i];
    return sum / n;
}
static double stddev(const double *v, int n, double mu) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double d = v[i] - mu;
        sum += d * d;
    }
    return sqrt(sum / n);
}
static int cmp_double(const void *a, const void *b) {
    double da = *(const double*)a, db = *(const double*)b;
    return (da < db) ? -1 : (da > db) ? 1 : 0;
}
static double median(double *v, int n) {
    qsort(v, n, sizeof(v[0]), cmp_double);
    if (n & 1) {
        return v[n/2];
    } else {
        return 0.5 * (v[n/2 - 1] + v[n/2]);
    }
}

int main(void) {
    // Pin to CPU 0 on Linux
  #ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
        perror("sched_setaffinity");
    }
  #endif

    const size_t sizes[] = {2<<10, 4<<10, 8<<10, 16<<10, 32<<10};
    const int    RUNS   = 100;
    const int    ITER   = 200;
    const int    NSZ    = sizeof(sizes)/sizeof(sizes[0]);

    // 1) Detailed per‐run CSV header
    puts("size,run,elapsed_ns,mbps,cycles,cpb");

    // 2) Reserve space for summary
    double mbps_mean[NSZ], mbps_sd[NSZ], mbps_md[NSZ];
    double cpb_mean[NSZ],  cpb_sd[NSZ],  cpb_md[NSZ];

    for (int si = 0; si < NSZ; si++) {
        size_t N = sizes[si];

        // Allocate aligned buffers
        u8 *in = NULL, *out = NULL;
        if (posix_memalign((void**)&in,  64, N) != 0 ||
            posix_memalign((void**)&out, 64, N) != 0) {
            fprintf(stderr, "posix_memalign failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        memset(in, 0xA5, N);

        // Load fixed key into an __m128i
        const u8 fixed_key[16] = {
            0x2b,0x7e,0x15,0x16, 0x28,0xae,0xd2,0xa6,
            0xab,0xf7,0x15,0x88, 0x09,0xcf,0x4f,0x3c
        };
        __m128i key = _mm_loadu_si128((const __m128i*)fixed_key);

        // Warm-up
        for (int w = 0; w < 10; w++) {
            for (size_t off = 0; off < N; off += 16) {
                __m128i blk = _mm_loadu_si128((const __m128i*)(in + off));
                __m128i enc = aes(key, blk);
                _mm_storeu_si128((__m128i*)(out + off), enc);
            }
        }

        // Allocate stats arrays
        double *mbps = malloc(sizeof(*mbps) * RUNS);
        double *cpb  = malloc(sizeof(*cpb ) * RUNS);

        // Timed runs
        for (int run = 0; run < RUNS; run++) {
            struct timespec t0, t1;
            u64 c0, c1;

            clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
            c0 = rdtsc();
            for (int it = 0; it < ITER; it++) {
                for (size_t off = 0; off < N; off += 16) {
                    __m128i blk = _mm_loadu_si128((const __m128i*)(in + off));
                    __m128i enc = aes(key, blk);
                    _mm_storeu_si128((__m128i*)(out + off), enc);
                }
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            c1 = rdtsc();

            u64 dt_ns   = diff_ns(&t0, &t1);
            double secs = dt_ns / 1e9;
            double bytes= (double)N * ITER;
            double mbs  = bytes / (1024.0*1024.0) / secs;
            u64 cycles  = c1 - c0;
            double cpbv = cycles / bytes;

            mbps[run] = mbs;
            cpb [run] = cpbv;

            // Print per-run CSV line
            printf("%zu,%d,%" PRIu64 ",%.2f,%" PRIu64 ",%.2e\n",
                   N, run, dt_ns, mbs, cycles, cpbv);
        }

        // Compute summary stats
        double m_mu = mean(mbps, RUNS);
        double m_sd = stddev(mbps, RUNS, m_mu);
        double m_md = median(mbps, RUNS);
        double c_mu = mean(cpb,   RUNS);
        double c_sd = stddev(cpb,   RUNS, c_mu);
        double c_md = median(cpb,   RUNS);

        mbps_mean[si] = m_mu;
        mbps_sd[si]   = m_sd;
        mbps_md[si]   = m_md;
        cpb_mean[si]  = c_mu;
        cpb_sd[si]    = c_sd;
        cpb_md[si]    = c_md;

        free(in); free(out);
        free(mbps); free(cpb);
    }

    // 3) Print summary CSV
    puts("\n# summary over runs");
    puts("size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median");
    for (int si = 0; si < NSZ; si++) {
        printf("%zu,%.2f,%.2f,%.2f,%.2e,%.2e,%.2e\n",
               sizes[si],
               mbps_mean[si], mbps_sd[si], mbps_md[si],
               cpb_mean[si],  cpb_sd[si],  cpb_md[si]);
    }

    return 0;
}


