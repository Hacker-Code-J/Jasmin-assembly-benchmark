// gcc -std=c11 -O2 -Wall bench_ossl_sha3.c ossl_sha3.c keccak1600.c -o bench_ossl_sha3 -lm
// ./bench_ossl_sha3 > bench_aesni.csv

// gcc -m64 -O2 -Wall -c aesni-x86_64.S -o aesni.o
// gcc -O2 -Wall -c bench_aesni.c     -o bench_aesni.o
// gcc -O2 -maes -mssse3 aesni.o bench_aesni.o -lm -o bench_aesni
// ./bench_aesni > bench_aesni.csv

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

/* your SHA3 implementations: */
#include "ossl_sha3.h"
/* which must declare:
   void ossl_sha3_reset(KECCAK1600_CTX *ctx);
   int  ossl_sha3_init(KECCAK1600_CTX *ctx, unsigned char pad, size_t bitlen);
   int  ossl_keccak_init(KECCAK1600_CTX *ctx, unsigned char pad,
                         size_t typelen, size_t mdlen);
   int  ossl_sha3_update(KECCAK1600_CTX *ctx, const void *_inp, size_t len);
   int  ossl_sha3_final(KECCAK1600_CTX *ctx, unsigned char *out, size_t outlen);
   int  ossl_sha3_squeeze(KECCAK1600_CTX *ctx, unsigned char *out, size_t outlen);
   size_t SHA3_absorb(uint64_t A[5][5], const unsigned char *inp, size_t len,
                      size_t r);
*/

typedef uint8_t  u8;
typedef uint64_t u64;

/* rdtsc cycle counter */
static inline u64 rdtsc(void) {
    unsigned hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return ((u64)hi << 32) | lo;
}

/* nanosecond diff */
static inline u64 diff_ns(const struct timespec *s,
                          const struct timespec *e) {
    return (e->tv_sec - s->tv_sec)*1000000000ULL + (e->tv_nsec - s->tv_nsec);
}

/* stats helpers */
static double mean(const double *v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += v[i];
    return sum/n;
}
static int cmp_double(const void *a, const void *b) {
    double da = *(const double*)a, db = *(const double*)b;
    return (da<db)? -1 : (da>db)? 1 : 0;
}
static double median(double *v, int n) {
    qsort(v, n, sizeof *v, cmp_double);
    return (n&1) ? v[n/2] : 0.5*(v[n/2-1] + v[n/2]);
}
static double stddev(const double *v, int n, double mu) {
    double sum=0;
    for(int i=0;i<n;i++){ double d=v[i]-mu; sum += d*d; }
    return sqrt(sum/n);
}

int main(void) {
  #ifdef __linux__
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset); CPU_SET(0,&cpuset);
    if (sched_setaffinity(0, sizeof cpuset, &cpuset) != 0)
      perror("sched_setaffinity");
  #endif

    const size_t sizes[] = {  2<<10,  4<<10,  8<<10, 16<<10, 32<<10 };
    const int    RUNS     = 100;
    const int    ITER     = 200;
    const int    NSZ      = sizeof(sizes)/sizeof(sizes[0]);

    puts("size,run,elapsed_ns,mbps,cycles,cpb");

    double mbps_mean[NSZ], mbps_sd[NSZ], mbps_md[NSZ];
    double cpb_mean[NSZ],  cpb_sd[NSZ],  cpb_md[NSZ];

    for (int si = 0; si < NSZ; si++) {
        size_t N = sizes[si];

        /* buffers */
        u8 *in = NULL, *out = NULL, *digest = malloc(64);
        if (posix_memalign((void**)&in,  64, N) != 0 ||
            posix_memalign((void**)&out, 64, N) != 0) {
            perror("posix_memalign"); exit(1);
        }
        memset(in,  0x5A, N);

        /* context */
        KECCAK1600_CTX ctx;
        /* warm-up */
        ossl_sha3_init(&ctx, 0x06, 256);
        ossl_sha3_update(&ctx, in, N);
        ossl_sha3_final(&ctx, digest, 32);

        double *mbps = malloc(sizeof*mbps * RUNS);
        double *cpb  = malloc(sizeof*cpb  * RUNS);

        for (int run = 0; run < RUNS; run++) {
            struct timespec t0, t1; u64 c0, c1;
            clock_gettime(CLOCK_MONOTONIC_RAW, &t0);
            c0 = rdtsc();
            for (int i = 0; i < ITER; i++) {
                ossl_sha3_reset(&ctx);
                ossl_sha3_init(&ctx, 0x06, 256);
                ossl_sha3_update(&ctx, in, N);
                ossl_sha3_final(&ctx, digest, 32);
            }
            clock_gettime(CLOCK_MONOTONIC_RAW, &t1);
            c1 = rdtsc();

            u64 dt = diff_ns(&t0,&t1);
            double secs = dt/1e9;
            double mb   = (double)N * ITER / (1024.*1024.) / secs;
            u64    cyc  = c1 - c0;
            double cpbv = (double)cyc / ((double)N*ITER);

            printf("%zu,%d,%" PRIu64 ",%.2f,%" PRIu64 ",%.2e\n",
                   N, run, dt, mb, cyc, cpbv);

            mbps[run] = mb;
            cpb [run] = cpbv;
        }

        /* summarize */
        double m_mu = mean(mbps,RUNS), m_sd=stddev(mbps,RUNS,m_mu),
               m_md = median(mbps,RUNS);
        double c_mu = mean(cpb, RUNS), c_sd=stddev(cpb,RUNS,c_mu),
               c_md = median(cpb, RUNS);

        mbps_mean[si]=m_mu; mbps_sd[si]=m_sd; mbps_md[si]=m_md;
        cpb_mean[si]=c_mu;  cpb_sd[si]=c_sd;  cpb_md[si]=c_md;

        free(in); free(out);
        free(mbps); free(cpb);
    }

    puts("\n# summary");
    puts("size,mbps_mean,mbps_stddev,mbps_median,cpb_mean,cpb_stddev,cpb_median");
    for(int i=0;i<5;i++){
        printf("%zu,%.2f,%.2f,%.2f,%.2e,%.2e,%.2e\n",
               sizes[i],
               mbps_mean[i], mbps_sd[i], mbps_md[i],
               cpb_mean[i],  cpb_sd[i],  cpb_md[i]);
    }

    return 0;
}
