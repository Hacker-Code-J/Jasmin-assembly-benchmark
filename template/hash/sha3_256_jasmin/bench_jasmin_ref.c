// gcc -std=c11 -O2 -Wall -maes -mssse3 -mavx bench_jasmin_ref.c sha3_256_ref.S -o bench_jasmin_ref -lm
// ./bench_jasmin_aes > jasmin_results.csv
#define _POSIX_C_SOURCE 200809L
#ifdef __linux__
  #define _GNU_SOURCE
  #include <sched.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <inttypes.h>
#include <math.h>

/* declare your function: */
extern int jade_hash_sha3_256_amd64_ref(
    uint8_t *hash,
    const uint8_t *input,
    uint64_t input_length
);

typedef uint8_t  u8;
typedef uint64_t u64;

/* rdtsc cycle counter */
static inline u64 rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((u64)hi << 32) | lo;
}

/* ns diff */
static inline u64 diff_ns(const struct timespec *s,
                          const struct timespec *e) {
    return (e->tv_sec - s->tv_sec) * 1000000000ULL
         + (e->tv_nsec - s->tv_nsec);
}

/* stats helpers */
static double mean(const double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += v[i];
    return sum / n;
}
static int cmpd(const void *a, const void *b) {
    double da = *(double*)a, db = *(double*)b;
    return (da < db) ? -1 : (da > db) ? 1 : 0;
}
static double median(double *v, int n) {
    qsort(v, n, sizeof *v, cmpd);
    if (n & 1) return v[n/2];
    return 0.5 * (v[n/2 - 1] + v[n/2]);
}
static double stddev(const double *v, int n, double mu) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        double d = v[i] - mu;
        sum += d * d;
    }
    return sqrt(sum / n);
}

int main(void) {
  #ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    CPU_SET(0, &cpuset);
    if (sched_setaffinity(0, sizeof cpuset, &cpuset))
      perror("sched_setaffinity");
  #endif

    const size_t sizes[] = { 2<<10, 4<<10, 8<<10, 16<<10, 32<<10 };
    const int    RUNS   = 100;
    const int    ITER   = 200;
    const int    NSZ    = sizeof(sizes)/sizeof(sizes[0]);

    /* CSV header */
    puts("size,run,elapsed_ns,mbps,cycles,cpb");

    double mbps_mean[NSZ], mbps_sd[NSZ], mbps_md[NSZ];
    double cpb_mean[NSZ],  cpb_sd[NSZ],  cpb_md[NSZ];

    for (int si = 0; si < NSZ; si++) {
        size_t N = sizes[si];
        u8 *in = NULL, *out = NULL;
        u8  hash[32];

        if (posix_memalign((void**)&in,  64, N) ||
            posix_memalign((void**)&out, 64, N)) {
            fprintf(stderr, "posix_memalign: %s\n", strerror(errno));
            return 1;
        }
        memset(in, 0xA5, N);

        /* warm-up: */
        for (int w = 0; w < 10; w++)
            jade_hash_sha3_256_amd64_ref(hash, in, N);

        double *mbps = malloc(sizeof *mbps * RUNS);
        double *cpb  = malloc(sizeof *cpb  * RUNS);

        for (int run = 0; run < RUNS; run++) {
            struct timespec t0, t1;
            u64 c0, c1;
            clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
            c0 = rdtsc();
            for (int i = 0; i < ITER; i++) {
                jade_hash_sha3_256_amd64_ref(hash, in, N);
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            c1 = rdtsc();

            u64 dt   = diff_ns(&t0, &t1);
            double secs   = dt / 1e9;
            double mb     = (double)N * ITER / (1024.0*1024.0) / secs;
            u64    cycles = c1 - c0;
            double cpbv   = (double)cycles / ((double)N * ITER);

            printf("%zu,%d,%" PRIu64 ",%.2f,%" PRIu64 ",%.2e\n",
                   N, run, dt, mb, cycles, cpbv);

            mbps[run] = mb;
            cpb [run] = cpbv;
        }

        double mμ = mean(mbps, RUNS);
        double mσ = stddev(mbps, RUNS, mμ);
        double mδ = median(mbps, RUNS);
        double cμ = mean(cpb,  RUNS);
        double cσ = stddev(cpb, RUNS, cμ);
        double cδ = median(cpb, RUNS);

        mbps_mean[si] = mμ;  mbps_sd[si] = mσ;  mbps_md[si] = mδ;
        cpb_mean[si]  = cμ;  cpb_sd[si]  = cσ;  cpb_md[si]  = cδ;

        free(in);
        free(out);
        free(mbps);
        free(cpb);
    }

    puts("\n# summary");
    puts("size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median");
    for (int i = 0; i < NSZ; i++) {
        printf("%zu,%.2f,%.2f,%.2f,%.2e,%.2e,%.2e\n",
               sizes[i],
               mbps_mean[i], mbps_sd[i], mbps_md[i],
               cpb_mean[i],  cpb_sd[i],  cpb_md[i]);
    }

    return 0;
}
