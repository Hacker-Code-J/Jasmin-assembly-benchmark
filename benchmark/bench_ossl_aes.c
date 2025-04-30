// benches/bench_ossl_aes.c
// #define _POSIX_C_SOURCE 199309L
#define _POSIX_C_SOURCE 200809L
#ifdef __linux__
  #define _GNU_SOURCE
  #include <sched.h>
#endif
#include <errno.h>
#include "../include/jab_setup.h"   // your typedefs for u8, size_t, etc.
#include "../include//openssl/ossl_aes.h"    // your renamed aes header

// rdtsc cycle counter
static inline u64 rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((u64)hi << 32) | lo;
}

// nanosecond diff
static inline u64 diff_ns(const struct timespec *s, const struct timespec *e) {
    return (e->tv_sec - s->tv_sec) * 1000000000ULL + (e->tv_nsec - s->tv_nsec);
}

// stats helpers
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
    const int RUNS = 100;
    const int ITER = 200;

    // 1) Detailed per‐run CSV header
    puts("size,run,elapsed_ns,mbps,cycles,cpb");

    // 2) Reserve space for summary
    double summary_mbps_mean[sizeof(sizes)/sizeof(sizes[0])];
    double summary_mbps_sd[sizeof(sizes)/sizeof(sizes[0])];
    double summary_mbps_md[sizeof(sizes)/sizeof(sizes[0])];
    double summary_cpb_mean[sizeof(sizes)/sizeof(sizes[0])];
    double summary_cpb_sd[sizeof(sizes)/sizeof(sizes[0])];
    double summary_cpb_md[sizeof(sizes)/sizeof(sizes[0])];

    // Loop over each buffer size
    for (int si = 0; si < (int)(sizeof(sizes)/sizeof(*sizes)); si++) {
        size_t N = sizes[si];

        // Allocate aligned buffers
        u8 *in = NULL, *out = NULL;
        if (posix_memalign((void**)&in, 64, N) != 0 ||
            posix_memalign((void**)&out,64, N) != 0) {
            fprintf(stderr, "posix_memalign failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        memset(in, 0xA5, N);

        // Set up AES key
        AES_KEY key;
        u8 fixed_key[16] = {
            0x2b,0x7e,0x15,0x16, 0x28,0xae,0xd2,0xa6,
            0xab,0xf7,0x15,0x88, 0x09,0xcf,0x4f,0x3c
        };
        if (AES_set_encrypt_key(fixed_key, 128, &key) < 0) {
            fprintf(stderr, "AES_set_encrypt_key failed\n");
            free(in); free(out);
            return EXIT_FAILURE;
        }

        // Warm-up loop
        for (int w = 0; w < 10; w++) {
            for (size_t off = 0; off < N; off += 16) {
                AES_encrypt(in + off, out + off, &key);
            }
        }

        // Prepare arrays
        double *mbps = malloc(sizeof(double) * RUNS);
        double *cpb  = malloc(sizeof(double) * RUNS);

        // Perform runs
        for (int run = 0; run < RUNS; run++) {
            struct timespec t0, t1;
            u64 c0, c1;

            clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
            c0 = rdtsc();
            for (int i = 0; i < ITER; i++) {
                for (size_t off = 0; off < N; off += 16) {
                    AES_encrypt(in + off, out + off, &key);
                }
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            c1 = rdtsc();

            u64 dt_ns   = diff_ns(&t0, &t1);
            double secs = dt_ns / 1e9;
            double bytes= (double)N * ITER;
            double m    = bytes / (1024.0*1024.0) / secs;
            u64 cycles  = c1 - c0;
            double cpbv = cycles / bytes;

            mbps[run] = m;
            cpb [run] = cpbv;

            // Print per‐run CSV line
            printf("%zu,%d,%" PRIu64 ",%.2f,%" PRIu64 ",%.2e\n",
                   N, run, dt_ns, m, cycles, cpbv);
        }

        // Compute summary stats for this size
        double m_mu = mean(mbps, RUNS);
        double m_sd = stddev(mbps, RUNS, m_mu);
        double m_md = median(mbps, RUNS);
        double c_mu = mean(cpb,  RUNS);
        double c_sd = stddev(cpb,  RUNS, c_mu);
        double c_md = median(cpb,  RUNS);

        summary_mbps_mean[si] = m_mu;
        summary_mbps_sd[si]   = m_sd;
        summary_mbps_md[si]   = m_md;
        summary_cpb_mean[si]  = c_mu;
        summary_cpb_sd[si]    = c_sd;
        summary_cpb_md[si]    = c_md;

        free(in);
        free(out);
        free(mbps);
        free(cpb);
    }

    // 3) Print summary CSV
    puts("\n# summary over runs");
    puts("size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median");
    for (int si = 0; si < (int)(sizeof(sizes)/sizeof(*sizes)); si++) {
        printf("%zu,%.2f,%.2f,%.2f,%.2e,%.2e,%.2e\n",
               sizes[si],
               summary_mbps_mean[si],
               summary_mbps_sd[si],
               summary_mbps_md[si],
               summary_cpb_mean[si],
               summary_cpb_sd[si],
               summary_cpb_md[si]);
    }

    return 0;
}


// // rdtsc cycle counter
// static inline u64 rdtsc(void) {
//     unsigned hi, lo;
//     __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
//     return ((u64)hi << 32) | lo;
// }

// // nanosecond diff
// static inline u64 diff_ns(const struct timespec *s, const struct timespec *e) {
//     return (e->tv_sec - s->tv_sec) * 1000000000ULL + (e->tv_nsec - s->tv_nsec);
// }

// // stats helpers
// static double mean(const double *v, int n) {
//     double sum = 0;
//     for (int i = 0; i < n; i++) sum += v[i];
//     return sum / n;
// }
// static double stddev(const double *v, int n, double mu) {
//     double sum = 0;
//     for (int i = 0; i < n; i++) {
//         double d = v[i] - mu;
//         sum += d * d;
//     }
//     return sqrt(sum / n);
// }
// static int cmp_double(const void *a, const void *b) {
//     double da = *(const double*)a, db = *(const double*)b;
//     return (da < db) ? -1 : (da > db) ? 1 : 0;
// }
// static double median(double *v, int n) {
//     qsort(v, n, sizeof(v[0]), cmp_double);
//     if (n & 1) {
//         return v[n/2];
//     } else {
//         return 0.5 * (v[n/2 - 1] + v[n/2]);
//     }
// }

// int main(void) {
//     // Pin to CPU 0 on Linux
// #ifdef __linux__
//     cpu_set_t cpuset;
//     CPU_ZERO(&cpuset);
//     CPU_SET(0, &cpuset);
//     if (sched_setaffinity(0, sizeof(cpuset), &cpuset) != 0) {
//         perror("sched_setaffinity");
//         // not fatal
//     }
// #endif

//     const size_t sizes[] = {2<<10, 4<<10, 8<<10, 16<<10, 32<<10};
//     const int RUNS = 100;
//     const int ITER = 200;

//     // Detailed per-run CSV header
//     printf("size,run,elapsed_ns,mbps,cycles,cpb\n");

//     // JSON summary start
//     printf("{\n  \"summary\": [\n");

//     for (int si = 0; si < (int)(sizeof(sizes)/sizeof(*sizes)); si++) {
//         size_t N = sizes[si];

//         // Allocate aligned buffers
//         u8 *in = NULL, *out = NULL;
//         int rc = posix_memalign((void**)&in, 64, N);
//         if (rc) {
//             fprintf(stderr, "posix_memalign(in) failed: %s\n", strerror(rc));
//             exit(EXIT_FAILURE);
//         }
//         rc = posix_memalign((void**)&out, 64, N);
//         if (rc) {
//             fprintf(stderr, "posix_memalign(out) failed: %s\n", strerror(rc));
//             free(in);
//             exit(EXIT_FAILURE);
//         }
//         memset(in, 0xA5, N);

//         // Set up AES key
//         AES_KEY key;
//         u8 fixed_key[16] = {
//             0x2b,0x7e,0x15,0x16, 0x28,0xae,0xd2,0xa6,
//             0xab,0xf7,0x15,0x88, 0x09,0xcf,0x4f,0x3c
//         };
//         if (AES_set_encrypt_key(fixed_key, 128, &key) < 0) {
//             fprintf(stderr, "AES_set_encrypt_key failed\n");
//             free(in); free(out);
//             return EXIT_FAILURE;
//         }

//         // Warm-up loop
//         for (int w = 0; w < 10; w++) {
//             for (size_t off = 0; off < N; off += 16) {
//                 AES_encrypt(in + off, out + off, &key);
//             }
//         }

//         // Prepare arrays
//         double *mbps = malloc(sizeof(double) * RUNS);
//         double *cpb  = malloc(sizeof(double) * RUNS);

//         // Perform runs
//         for (int run = 0; run < RUNS; run++) {
//             struct timespec t0, t1;
//             u64 c0, c1;

//             clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
//             c0 = rdtsc();
//             for (int i = 0; i < ITER; i++) {
//                 for (size_t off = 0; off < N; off += 16) {
//                     AES_encrypt(in + off, out + off, &key);
//                 }
//             }
//             clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
//             c1 = rdtsc();

//             u64 dt_ns    = diff_ns(&t0, &t1);
//             double secs  = dt_ns / 1e9;
//             double bytes = (double)N * ITER;
//             double m     = bytes / (1024.0*1024.0) / secs;
//             u64 cycles   = c1 - c0;
//             double cpbv  = cycles / bytes;

//             mbps[run] = m;
//             cpb[run]  = cpbv;

//             // CSV line
//             printf("%zu,%d,%" PRIu64 ",%.2f,%" PRIu64 ",%.2e\n",
//                    N, run, dt_ns, m, cycles, cpbv);
//         }

//         // Compute stats
//         double m_mu = mean(mbps, RUNS);
//         double m_sd = stddev(mbps, RUNS, m_mu);
//         double m_md = median(mbps, RUNS);
//         double c_mu = mean(cpb, RUNS);
//         double c_sd = stddev(cpb, RUNS, c_mu);
//         double c_md = median(cpb, RUNS);

//         // JSON summary entry
//         printf("    {\n"
//                "      \"size\": %zu,\n"
//                "      \"runs\": %d,\n"
//                "      \"mbps_mean\": %.2f,\n"
//                "      \"mbps_stddev\": %.2f,\n"
//                "      \"mbps_median\": %.2f,\n"
//                "      \"cpb_mean\": %.2e,\n"
//                "      \"cpb_stddev\": %.2e,\n"
//                "      \"cpb_median\": %.2e\n"
//                "    }%s\n",
//                N, RUNS,
//                m_mu, m_sd, m_md,
//                c_mu, c_sd, c_md,
//                (si + 1 < (int)(sizeof(sizes)/sizeof(*sizes))) ? "," : "");

//         free(in);
//         free(out);
//         free(mbps);
//         free(cpb);
//     }

//     // JSON summary end
//     printf("  ]\n}\n");

//     return 0;
// }