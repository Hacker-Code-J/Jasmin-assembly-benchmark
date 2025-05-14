#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "KeccakP-1600-SnP.h"

// gcc -std=c99 -O2 -Wall -Wextra -m64 -c bench.c   -o bench.o
// gcc -m64 bench.o keccak_ref.o -o keccak_bench_c
// gcc -m64 -no-pie bench.o keccak_asm.o -o keccak_bench_asm

// gcc -mavx2 bench.o keccak_avx2.o -o keccak_bench_avx2

// Read timestamp counter (serialize with CPUID)
static inline uint64_t rdtsc_begin(void) {
    uint32_t lo, hi;
    __asm__ __volatile__ (
        "cpuid\n\t"          // serialize
        "rdtsc\n\t"
        : "=a"(lo), "=d"(hi)
        :: "rbx","rcx"
    );
    return ((uint64_t)hi<<32)|lo;
}
static inline uint64_t rdtsc_end(void) {
    uint32_t lo, hi;
    __asm__ __volatile__ (
        "rdtscp\n\t"         // read + serialize
        "mov %%eax,%0\n\t"
        "mov %%edx,%1\n\t"
        "cpuid\n\t"          // serialize
        : "=r"(lo), "=r"(hi)
        :: "rax","rbx","rcx","rdx"
    );
    return ((uint64_t)hi<<32)|lo;
}

double bench_addbytes_stream(size_t total_length) {
    KeccakP1600_state s;
    static uint8_t data[1024];
    for (size_t i = 0; i < total_length; i++) data[i] = (uint8_t)i;
    KeccakP1600_Initialize(&s);

    // warm-up
    {
      size_t rem = total_length, pos = 0;
      while (rem) {
        size_t chunk = rem > 200 ? 200 : rem;
        KeccakP1600_AddBytes(&s, data + pos, 0, chunk);
        rem -= chunk;
        pos += chunk;
      }
    }

    uint64_t t0 = rdtsc_begin();
    for (int r = 0; r < 1000; r++) {
      size_t rem = total_length, pos = 0;
      while (rem) {
        size_t chunk = rem > 200 ? 200 : rem;
        KeccakP1600_AddBytes(&s, data + pos, 0, chunk);
        rem -= chunk;
        pos += chunk;
      }
    }
    uint64_t t1 = rdtsc_end();
    double bytes = (double)total_length * 1000;
    return (double)((t1 - t0) / bytes);
}

#define ITERS 10000000

double bench_initialize() {
    KeccakP1600_state s;
    // warm up cache
    KeccakP1600_Initialize(&s);

    uint64_t t0 = rdtsc_begin();
    for (int i = 0; i < ITERS; i++) {
        KeccakP1600_Initialize(&s);
    }
    uint64_t t1 = rdtsc_end();
    return (double)((t1 - t0) / ITERS);
}

double bench_addbyte(void) {
    KeccakP1600_state s;
    KeccakP1600_Initialize(&s);

    const unsigned offset = 0;
    uint64_t t0 = rdtsc_begin();
    for (uint32_t i = 0; i < ITERS; i++) {
        KeccakP1600_AddByte(&s, 0xFF, offset);
    }
    uint64_t t1 = rdtsc_end();
    return (double)((t1 - t0) / ITERS);
}

double bench_addbytes(size_t length) {
    KeccakP1600_state s;
    static uint8_t data[4096];
    KeccakP1600_Initialize(&s);

    // fill data with pseudo-random
    for (size_t i = 0; i < length; i++) data[i] = (uint8_t)i;

    const int rounds = 1000;
    uint64_t t0 = rdtsc_begin();
    for (int r = 0; r < rounds; r++) {
        KeccakP1600_AddBytes(&s, data, /*offset*/0, length);
    }
    uint64_t t1 = rdtsc_end();
    double bytes = (double)length * rounds;
    return (double)((t1 - t0) / bytes);  // cycles per byte
}

// uint64_t bench_permute_12() {
//     KeccakP1600_state s;
//     KeccakP1600_Initialize(&s);
//     uint64_t t0 = rdtsc_begin();
//     for (int i = 0; i < ITERS; i++) {
//         KeccakP1600_Permute_12rounds(&s);
//     }
//     uint64_t t1 = rdtsc_end();
//     return (t1 - t0) / ITERS;
// }

double bench_permute_24() { 
    KeccakP1600_state s;
    KeccakP1600_Initialize(&s);
    uint64_t t0 = rdtsc_begin();
    for (int i = 0; i < ITERS; i++) {
        KeccakP1600_Permute_24rounds(&s);
    }
    uint64_t t1 = rdtsc_end();
    return (double)((t1 - t0) / ITERS);
}

// uint64_t bench_permute_n(unsigned n) {
//     KeccakP1600_state s;
//     KeccakP1600_Initialize(&s);
//     uint64_t t0 = rdtsc_begin();
//     for (int i = 0; i < ITERS; i++) {
//         KeccakP1600_Permute_Nrounds(&s, n);
//     }
//     uint64_t t1 = rdtsc_end();
//     return (t1 - t0) / ITERS;
// }

int main(void) {
    printf("Initialize:       %f cycles/call\n", bench_initialize());
    printf("AddByte:          %f cycles/call\n", bench_addbyte());
    size_t lengths[] = { 1, 8, 64, 256, 1024, 2048 };
    size_t num_lengths = sizeof(lengths)/sizeof(lengths[0]);
    // for (size_t i = 0; i < num_lengths; i++) {
    //     size_t L = lengths[i];
    //     printf("AddBytes[%4zu]:    %lu cycles/byte\n",
    //         L, bench_addbytes(L));
    // }
    for (size_t i = 0; i < num_lengths; i++) {
        size_t L = lengths[i];
        printf("AddBytes-stream[%4zu]: %8f cycles/byte\n",
            L, bench_addbytes_stream(L));
    }
    // repeat for OverwriteBytes, OverwriteWithZeroes, ExtractBytes, ExtractAndAddBytes
    // printf("Permute-12:       %lu cycles/call\n", bench_permute_12());
    printf("Permute-24:       %f cycles/call\n", bench_permute_24());
    // printf("Permute-N(6):     %lu cycles/call\n", bench_permute_n(6));
    // printf("Permute-N(24):    %lu cycles/call\n", bench_permute_n(24));
    return 0;
}

