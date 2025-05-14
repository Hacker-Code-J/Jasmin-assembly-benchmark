/*
 * Benchmark for KeccakP-1600 permutations (12 and 24 rounds)
 * using 64-bit optimized x86 assembler implementation.
 * Measures cycles and nanoseconds per call with per-run CSV and summary.
 */
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>
#include "./keccackP-1600_jazz_ref.h"

#ifdef __linux__  // Only for Linux systems
#define __USE_GNU
#include <sched.h>  // Include the required header for CPU_ZERO, CPU_SET, sched_setaffinity
#endif

typedef uint64_t    u64;
typedef uint8_t     u8;

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
 
// Jade Hash SHA3-256 Reference Implementation
// extern int jade_hash_sha3_256_amd64_ref(uint8_t *hash, const uint8_t *input, uint64_t input_length);

// Keccak Hash Function Evaluation (Absorb + Permute + Squeeze)
void keccak_hash(uint8_t *out, size_t outlen, uint8_t *in, size_t inlen) {
    int result = jade_hash_sha3_256_amd64_ref(out, in, inlen);
    if (result != 0) {
        fprintf(stderr, "Error in hashing function: %d\n", result);
        exit(EXIT_FAILURE);
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

    const size_t sizes[] = {1 << 10, 2 << 10, 4 << 10, 8 << 10, 16 << 10};  // Sizes: 1 KB, 2KB, 4KB, 8KB, 16KB
    const int RUNS = 10000;
    const int ITER = 1000;

    // 1) Detailed per-run CSV header
    puts("size,run,elapsed_ns,mbps,cycles,cpb");

    // 2) Reserve space for summary
    double summary_mbps_mean[sizeof(sizes) / sizeof(sizes[0])];
    double summary_mbps_sd[sizeof(sizes) / sizeof(sizes[0])];
    double summary_mbps_md[sizeof(sizes) / sizeof(sizes[0])];
    double summary_cpb_mean[sizeof(sizes) / sizeof(sizes[0])];
    double summary_cpb_sd[sizeof(sizes) / sizeof(sizes[0])];
    double summary_cpb_md[sizeof(sizes) / sizeof(sizes[0])];

    // Loop over each buffer size
    for (int si = 0; si < (int)(sizeof(sizes) / sizeof(*sizes)); si++) {
        size_t N = sizes[si];
        uint8_t *input = malloc(N);
        uint8_t *output = malloc(32);  // SHA3-256 output size
        if (input == NULL || output == NULL) {
            fprintf(stderr, "Memory allocation failed: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        memset(input, 0xA5, N);  // Initialize input buffer with a pattern

        // Prepare arrays to hold results
        double *mbps = malloc(sizeof(double) * RUNS);
        double *cpb  = malloc(sizeof(double) * RUNS);

        // Perform runs
        for (int run = 0; run < RUNS; run++) {
            struct timespec t0, t1;
            uint64_t c0, c1;

            clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
            c0 = rdtsc();
            for (int i = 0; i < ITER; i++) {
                keccak_hash(output, 32, input, N);  // Use jade_hash_sha3_256_amd64_ref for hashing
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            c1 = rdtsc();

            uint64_t dt_ns   = diff_ns(&t0, &t1);
            double secs = dt_ns / 1e9;
            double bytes = (double)N * ITER;  // Number of bytes processed
            double m    = bytes / (1024.0 * 1024.0) / secs;  // Megabytes per second
            uint64_t cycles  = c1 - c0;
            double cpbv = cycles / bytes;  // Cycles per byte

            mbps[run] = m;
            cpb[run] = cpbv;

            // Print per-run CSV line
            printf("%zu,%d,%" PRIu64 ",%.2f,%" PRIu64 ",%.2e\n",
                   N, run, dt_ns, m, cycles, cpbv);
        }

        // Compute summary stats for this size
        double m_mu = mean(mbps, RUNS);
        double m_sd = stddev(mbps, RUNS, m_mu);
        double m_md = median(mbps, RUNS);
        double c_mu = mean(cpb,  RUNS);
        double c_sd = stddev(cpb,  RUNS, c_mu);
        double c_md = median(cpb, RUNS);

        summary_mbps_mean[si] = m_mu;
        summary_mbps_sd[si]   = m_sd;
        summary_mbps_md[si]   = m_md;
        summary_cpb_mean[si]  = c_mu;
        summary_cpb_sd[si]    = c_sd;
        summary_cpb_md[si]    = c_md;

        free(input);
        free(output);
        free(mbps);
        free(cpb);
    }

    // 3) Print summary CSV
    puts("\n# summary over runs");
    puts("size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median");
    for (int si = 0; si < (int)(sizeof(sizes) / sizeof(*sizes)); si++) {
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