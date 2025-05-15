#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "KeccakP-1600-SnP.h"
#define SHA3_256_RATE     136   /* 1088 bits = 136 bytes */
#define SHA3_256_OUTBYTES 32    /* 256 bits */

#define SHA3_384_RATE     104   /* 832 bits = 104 bytes */
#define SHA3_384_OUTBYTES 48    /* 384 bits */

#define SHA3_512_RATE     72    /* 576 bits =  72 bytes */
#define SHA3_512_OUTBYTES 64    /* 512 bits */

/* REF */
// gcc -std=c99 -O2 -Wall -Wextra -m64 -c bench.c   -o bench.o
// gcc -m64 bench.o keccak_ref.o -o bench_sha3_c_xkcp

/* x86_64 */
// gcc -std=c99 -O2 -Wall -Wextra -m64 -c bench.c   -o bench.o
// gcc -m64 -no-pie bench.o keccak_asm.o -o bench_sha3_x86_64_xkcp

/* AVX2 */
// gcc -std=c99 -O2 -Wall -Wextra -m64 -c bench.c   -o bench.o
// gcc -mavx2 bench.o keccak_avx2.o -o bench_sha3_avx2_xkcp

/* Jasmin-x86_64 */
// gcc -DJASMIN -std=c99 -O2 -Wall -Wextra -m64 -c bench.c   -o bench.o
// gcc -m64 -no-pie bench.o sha3_256_ref_jasmin.o sha3_384_ref_jasmin.o sha3_512_ref_jasmin.o -o bench_sha3_x86_64_libjade

/* Jasmin-avx2 */
// gcc -DJASMIN -std=c99 -O2 -Wall -Wextra -m64 -c bench.c   -o bench.o
// gcc -mavx2 bench.o sha3_256_avx2_jasmin.o sha3_384_avx2_jasmin.o sha3_512_avx2_jasmin.o -o bench_sha3_avx2_libjade

/* REF TEST (XKCP) */
// gcc -O3 -Wall -Wextra -m64 -c KeccakP-1600-reference.c -o KeccakP-1600-reference.o
// gcc -O3 -march=native -flto -funroll-loops -o benchmark_c_xkcp bench.c KeccakP-1600-reference.o

/* ASM TEST (XKCP) */
// as -o KeccakP-1600-x86-64.o KeccakP-1600-x86-64.s
// as -march=avx2 -o KeccakP-1600-AVX2.o KeccakP-1600-AVX2.s
// gcc -O3 -march=native -no-pie -flto -funroll-loops -o benchmark_x86_64_xkcp bench.c KeccakP-1600-x86-64.o
// gcc -O3 -march=native -mavx2 -flto -funroll-loops -o benchmark_avx2_xkcp bench.c KeccakP-1600-AVX2.o

/* ASM TEST (Libjade) */
// as -o sha3_256_ref_jasmin.o sha3_256_ref.s
// as -o sha3_384_ref_jasmin.o sha3_384_ref.s
// as -o sha3_512_ref_jasmin.o sha3_512_ref.s
// as -march=avx2 -o sha3_256_avx2_jasmin.o sha3_256_avx2.s
// as -march=avx2 -o sha3_384_avx2_jasmin.o sha3_384_avx2.s
// as -march=avx2 -o sha3_512_avx2_jasmin.o sha3_512_avx2.s
// gcc -DJASMIN -O3 -funroll-loops -flto -o benchmark_x86_64_libjade bench.c sha3_256_ref_jasmin.o sha3_384_ref_jasmin.o sha3_512_ref_jasmin.o
// gcc -DJASMIN -O3 -mavx2 -funroll-loops -flto -o benchmark_avx2_libjade bench.c sha3_256_avx2_jasmin.o sha3_384_avx2_jasmin.o sha3_512_avx2_jasmin.o

/* Perf */
// perf stat -e cache-references,cache-misses ./benchmark_avx2_xkcp
// perf stat -e cycles,instructions,cache-misses ./benchmark_avx2_xkcp

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

// double bench_addbytes_stream(size_t total_length) {
//     KeccakP1600_state s;
//     static uint8_t data[1024];
//     for (size_t i = 0; i < total_length; i++) data[i] = (uint8_t)i;
//     KeccakP1600_Initialize(&s);

//     // warm-up
//     {
//       size_t rem = total_length, pos = 0;
//       while (rem) {
//         size_t chunk = rem > 200 ? 200 : rem;
//         KeccakP1600_AddBytes(&s, data + pos, 0, chunk);
//         rem -= chunk;
//         pos += chunk;
//       }
//     }

//     uint64_t t0 = rdtsc_begin();
//     for (int r = 0; r < 1000; r++) {
//       size_t rem = total_length, pos = 0;
//       while (rem) {
//         size_t chunk = rem > 200 ? 200 : rem;
//         KeccakP1600_AddBytes(&s, data + pos, 0, chunk);
//         rem -= chunk;
//         pos += chunk;
//       }
//     }
//     uint64_t t1 = rdtsc_end();
//     double bytes = (double)total_length * 1000;
//     return (double)((t1 - t0) / bytes);
// }

// #define ITERS 10000000

// double bench_initialize() {
//     KeccakP1600_state s;
//     // warm up cache
//     KeccakP1600_Initialize(&s);

//     uint64_t t0 = rdtsc_begin();
//     for (int i = 0; i < ITERS; i++) {
//         KeccakP1600_Initialize(&s);
//     }
//     uint64_t t1 = rdtsc_end();
//     return (double)((t1 - t0) / ITERS);
// }

// double bench_addbyte(void) {
//     KeccakP1600_state s;
//     KeccakP1600_Initialize(&s);

//     const unsigned offset = 0;
//     uint64_t t0 = rdtsc_begin();
//     for (uint32_t i = 0; i < ITERS; i++) {
//         KeccakP1600_AddByte(&s, 0xFF, offset);
//     }
//     uint64_t t1 = rdtsc_end();
//     return (double)((t1 - t0) / ITERS);
// }

// double bench_addbytes(size_t length) {
//     KeccakP1600_state s;
//     static uint8_t data[4096];
//     KeccakP1600_Initialize(&s);

//     // fill data with pseudo-random
//     for (size_t i = 0; i < length; i++) data[i] = (uint8_t)i;

//     const int rounds = 1000;
//     uint64_t t0 = rdtsc_begin();
//     for (int r = 0; r < rounds; r++) {
//         KeccakP1600_AddBytes(&s, data, /*offset*/0, length);
//     }
//     uint64_t t1 = rdtsc_end();
//     double bytes = (double)length * rounds;
//     return (double)((t1 - t0) / bytes);  // cycles per byte
// }

// // uint64_t bench_permute_12() {
// //     KeccakP1600_state s;
// //     KeccakP1600_Initialize(&s);
// //     uint64_t t0 = rdtsc_begin();
// //     for (int i = 0; i < ITERS; i++) {
// //         KeccakP1600_Permute_12rounds(&s);
// //     }
// //     uint64_t t1 = rdtsc_end();
// //     return (t1 - t0) / ITERS;
// // }

// double bench_permute_24() { 
//     KeccakP1600_state s;
//     KeccakP1600_Initialize(&s);
//     uint64_t t0 = rdtsc_begin();
//     for (int i = 0; i < ITERS; i++) {
//         KeccakP1600_Permute_24rounds(&s);
//     }
//     uint64_t t1 = rdtsc_end();
//     return (double)((t1 - t0) / ITERS);
// }

// // uint64_t bench_permute_n(unsigned n) {
// //     KeccakP1600_state s;
// //     KeccakP1600_Initialize(&s);
// //     uint64_t t0 = rdtsc_begin();
// //     for (int i = 0; i < ITERS; i++) {
// //         KeccakP1600_Permute_Nrounds(&s, n);
// //     }
// //     uint64_t t1 = rdtsc_end();
// //     return (t1 - t0) / ITERS;
// // }
#ifdef JASMIN
extern int jade_hash_sha3_256_amd64(uint8_t *hash, const uint8_t *input, uint64_t input_length);
extern int jade_hash_sha3_384_amd64(uint8_t *hash, const uint8_t *input, uint64_t input_length);
extern int jade_hash_sha3_512_amd64(uint8_t *hash, const uint8_t *input, uint64_t input_length);
#else
int sha3_256(uint8_t *hash, const uint8_t *input, uint64_t input_length) {
    KeccakP1600_plain8_state state;
    KeccakP1600_Initialize(&state);

    uint64_t i;
    /* absorb all full RATE-byte blocks */
    for (i = 0; i + SHA3_256_RATE <= input_length; i += SHA3_256_RATE) {
        for (unsigned int j = 0; j < SHA3_256_RATE; j++)
            KeccakP1600_AddByte(&state, input[i + j], j);
        KeccakP1600_Permute_24rounds(&state);
    }
    /* absorb tail */
    unsigned int off = 0;
    for (; i < input_length; i++, off++)
        KeccakP1600_AddByte(&state, input[i], off);
    /* multi-rate padding */
    KeccakP1600_AddByte(&state, 0x06, off);
    KeccakP1600_AddByte(&state, 0x80, SHA3_256_RATE - 1);
    KeccakP1600_Permute_24rounds(&state);

    /* squeeze out digest */
    KeccakP1600_ExtractBytes(&state, hash, 0, SHA3_256_OUTBYTES);
    return 0;
}

/* SHA3-384 */
int sha3_384(uint8_t *hash, const uint8_t *input, uint64_t input_length) {
    KeccakP1600_plain8_state state;
    KeccakP1600_Initialize(&state);

    uint64_t i;
    for (i = 0; i + SHA3_384_RATE <= input_length; i += SHA3_384_RATE) {
        for (unsigned int j = 0; j < SHA3_384_RATE; j++)
            KeccakP1600_AddByte(&state, input[i + j], j);
        KeccakP1600_Permute_24rounds(&state);
    }
    unsigned int off = 0;
    for (; i < input_length; i++, off++)
        KeccakP1600_AddByte(&state, input[i], off);
    KeccakP1600_AddByte(&state, 0x06, off);
    KeccakP1600_AddByte(&state, 0x80, SHA3_384_RATE - 1);
    KeccakP1600_Permute_24rounds(&state);

    KeccakP1600_ExtractBytes(&state, hash, 0, SHA3_384_OUTBYTES);
    return 0;
}

/* SHA3-512 */
int sha3_512(uint8_t *hash, const uint8_t *input, uint64_t input_length) {
    KeccakP1600_plain8_state state;
    KeccakP1600_Initialize(&state);

    uint64_t i;
    for (i = 0; i + SHA3_512_RATE <= input_length; i += SHA3_512_RATE) {
        for (unsigned int j = 0; j < SHA3_512_RATE; j++)
            KeccakP1600_AddByte(&state, input[i + j], j);
        KeccakP1600_Permute_24rounds(&state);
    }
    unsigned int off = 0;
    for (; i < input_length; i++, off++)
        KeccakP1600_AddByte(&state, input[i], off);
    KeccakP1600_AddByte(&state, 0x06, off);
    KeccakP1600_AddByte(&state, 0x80, SHA3_512_RATE - 1);
    KeccakP1600_Permute_24rounds(&state);

    KeccakP1600_ExtractBytes(&state, hash, 0, SHA3_512_OUTBYTES);
    return 0;
}
// int sha3(uint8_t *hash, const uint8_t *input, uint64_t input_length) {
//     KeccakP1600_plain8_state state;
//     unsigned int offset = 0;

//     // Initialize Keccak state
//     KeccakP1600_Initialize(&state);

//     // Absorb the input bytes
//     for (unsigned int i = 0; i < input_length; i++) {
//         KeccakP1600_AddByte(&state, input[i], offset);
//         offset = (offset + 1) % 200;  // Keccak state is 200 bytes
//     }

//     // // Debug: print state after absorbing
//     // printf("State after absorbing input:\n");
//     // for (int i = 0; i < 200; i++) {
//     //     printf("%02x ", state.A[i]);
//     // }
//     // printf("\n");

//     // Padding step: Add padding byte 0x06
//     KeccakP1600_AddByte(&state, 0x06, offset);
//     offset = (offset + 1) % 200;  // Move to the next offset

//     // Add the 0x80 byte indicating the end of the message
//     KeccakP1600_AddByte(&state, 0x80, offset);
//     offset = (offset + 1) % 200;

//     // // Debug: print state after padding
//     // printf("State after padding:\n");
//     // for (int i = 0; i < 200; i++) {
//     //     printf("%02x ", state.A[i]);
//     // }
//     // printf("\n");

//     // Apply the 24 rounds of Keccak permutation
//     KeccakP1600_Permute_24rounds(&state);

//     // // Debug: print state after permutation
//     // printf("State after permutation:\n");
//     // for (int i = 0; i < 200; i++) {
//     //     printf("%02x ", state.A[i]);
//     // }
//     // printf("\n");

//     // Extract the hash (32 bytes for SHA3-256)
// #ifdef SHA3_384
//     KeccakP1600_ExtractBytes(&state, hash, 0, SHA3_384_HASH_SIZE); // For SHA3-256, we extract 32 bytes
// #elif SHA3_512
//     KeccakP1600_ExtractBytes(&state, hash, 0, SHA3_512_HASH_SIZE); // For SHA3-256, we extract 32 bytes
// #else
//     KeccakP1600_ExtractBytes(&state, hash, 0, 32); // For SHA3-256, we extract 32 bytes
// #endif
//     // // Debug: print the final hash
//     // printf("Extracted hash: ");
//     // for (int i = 0; i < 32; i++) {
//     //     printf("%02x", hash[i]);
//     // }
//     // printf("\n");

//     return 0; // Successful execution
// }
#endif

// Function to perform SHA-3 benchmark
#define CPU_FREQUENCY_GHZ 3.4  // Boost clock is 3.4 GHz
struct {
        const char *name;
        int  (*func)(uint8_t*,const uint8_t*,uint64_t);
        size_t hash_sz;
    } variants[3] = {
#ifdef JASMIN
        { "SHA3-256", jade_hash_sha3_256_amd64, SHA3_256_OUTBYTES },
        { "SHA3-384", jade_hash_sha3_384_amd64, SHA3_384_OUTBYTES },
        { "SHA3-512", jade_hash_sha3_512_amd64, SHA3_512_OUTBYTES },
#else
        { "SHA3-256", sha3_256, SHA3_256_OUTBYTES },
        { "SHA3-384", sha3_384, SHA3_384_OUTBYTES },
        { "SHA3-512", sha3_512, SHA3_512_OUTBYTES },
#endif
    };
// void benchmark_sha3(uint8_t *input, size_t input_size) { 
//     // print header once
//     static int first = 1;
//     if (first) {
//         printf("| Message Size  | %s(MB/s) | %s(MB/s) | %s(MB/s) | Latency (ms) | Cycles/byte |\n",
//             variants[0].name, variants[1].name, variants[2].name);
//         printf("|---------------|----------------|----------------|----------------|--------------|-------------|\n");
//         first = 0;
//     }

//     // we'll measure each variant
//     double throughputs[3];
//     double lat_ms[3], cyc_per_byte[3];

//     for (int v = 0; v < 3; v++) {
//         uint8_t  outbuf[variants[v].hash_sz];
//         uint64_t total_ticks = 0;
//         const int TRIALS = 10000;

//         for (int t = 0; t < TRIALS; t++) {
//             uint64_t t0 = rdtsc_begin();
//             variants[v].func(outbuf, input, input_size);
//             uint64_t t1 = rdtsc_end();
//             total_ticks += (t1 - t0);
//         }
//         double avg_ticks = (double)total_ticks / TRIALS;
//         // throughput MB/s
//         throughputs[v]    = (input_size / 1e6) / (avg_ticks / (CPU_FREQUENCY_GHZ * 1e9));
//         // latency in ms (single hash)
//         lat_ms[v]         = avg_ticks / (CPU_FREQUENCY_GHZ * 1e6);
//         // cycles per byte
//         cyc_per_byte[v]   = avg_ticks / input_size;
//     }

//     printf("| %10zu KB | %14.2f | %14.2f | %14.2f | %12.6f | %11.2f |\n",
//         input_size/1024,
//         throughputs[0], throughputs[1], throughputs[2],
//         lat_ms[0],   // report latency of the first (256) — you can pick any or average
//         cyc_per_byte[0]
//     );
// }
// call this once per message size
void benchmark_sha3(uint8_t *input, size_t input_size) {
    static int header_printed = 0;
    if (!header_printed) {
        // CSV header
        printf("Message Size");
        for(int v=0; v<3; v++)
            printf(",%s(MB/s)",        variants[v].name);
        for(int v=0; v<3; v++)
            printf(",%s Latency(ms)",   variants[v].name);
        for(int v=0; v<3; v++)
            printf(",%s Cycles/byte",    variants[v].name);
        printf("\n");
        header_printed = 1;
    }

    double throughputs[3];
    double lat_ms[3];
    double cyc_per_byte[3];

    const int TRIALS = 10000;
    for(int v=0; v<3; v++) {
        uint8_t outbuf[variants[v].hash_sz];
        uint64_t total_ticks = 0;
        // warm‐up (optional)
        // variants[v].func(outbuf, input, input_size);

        for(int t=0; t<TRIALS; t++) {
            uint64_t t0 = rdtsc_begin();
            variants[v].func(outbuf, input, input_size);
            uint64_t t1 = rdtsc_end();
            total_ticks += (t1 - t0);
        }

        double avg_ticks = (double)total_ticks / TRIALS;
        // throughput = bytes / second -> (input_size / 1e6) MB / (sec)
        throughputs[v] =
            (input_size / 1e6)
            / (avg_ticks / (CPU_FREQUENCY_GHZ * 1e9));
        // latency per call in ms
        lat_ms[v] =
            avg_ticks / (CPU_FREQUENCY_GHZ * 1e6);
        // cycles per input byte
        cyc_per_byte[v] =
            avg_ticks / (double)input_size;
    }

    // print one CSV line
    printf("%zu", input_size);
    for(int v=0; v<3; v++)
        printf(",%.2f", throughputs[v]);
    for(int v=0; v<3; v++)
        printf(",%.6f", lat_ms[v]);
    for(int v=0; v<3; v++)
        printf(",%.2f", cyc_per_byte[v]);
    printf("\n");
}

int main(void) {
    size_t sizes[] = {
        1 << 10, 2 << 10, 4 << 10, 8 << 10, 16 << 10, 32 << 10, 64 << 10, 128 << 10,
        256 << 10, 512 << 10, 1024 << 10}; // 1KB, 2KB, 4KB, 8KB, 16KB, 32KB, 64KB, 128KB, 256KB, 512KB, 1MB

    for (long unsigned int i = 0; i < sizeof(sizes)/sizeof(*sizes); i++) {
        uint8_t *buf = malloc(sizes[i]);
        memset(buf, 0xA5, sizes[i]);
        benchmark_sha3(buf, sizes[i]);
        free(buf);
    }

    // // Print header
    // printf("| Message Size | SHA3-256 Throughput (MB/s) | SHA3-384 Throughput (MB/s) | SHA3-512 Throughput (MB/s) | Latency (ms) | Latency (cycle/byte) |\n");
    // printf("| ------------ | -------------------------- | -------------------------- | -------------------------- | ------------ | -------------------- |\n");

    // // Benchmark each message size for SHA3-256, SHA3-384, and SHA3-512
    // for (size_t i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
    //     size_t input_size = sizes[i];
    //     uint8_t *input = malloc(input_size);
    //     assert(input != NULL);

    //     // Fill input with random data
    //     for (size_t j = 0; j < input_size; j++) {
    //         input[j] = rand() % 256;
    //     }

    //     // Run benchmarking for SHA3-256, SHA3-384, and SHA3-512
    //     benchmark_sha3(input, input_size, 256);
    //     memset(input, 0, input_size); // Clear input for next hash
    //     benchmark_sha3(input, input_size, 384);
    //     memset(input, 0, input_size); // Clear input for next hash
    //     benchmark_sha3(input, input_size, 512);

    //     // Clean up memory
    //     free(input);
    // }


    // printf("Initialize:       %f cycles/call\n", bench_initialize());
    // printf("AddByte:          %f cycles/call\n", bench_addbyte());
    // size_t lengths[] = { 1, 8, 64, 256, 1024, 2048 };
    // size_t num_lengths = sizeof(lengths)/sizeof(lengths[0]);
    // // for (size_t i = 0; i < num_lengths; i++) {
    // //     size_t L = lengths[i];
    // //     printf("AddBytes[%4zu]:    %lu cycles/byte\n",
    // //         L, bench_addbytes(L));
    // // }
    // for (size_t i = 0; i < num_lengths; i++) {
    //     size_t L = lengths[i];
    //     printf("AddBytes-stream[%4zu]: %8f cycles/byte\n",
    //         L, bench_addbytes_stream(L));
    // }
    // // repeat for OverwriteBytes, OverwriteWithZeroes, ExtractBytes, ExtractAndAddBytes
    // // printf("Permute-12:       %lu cycles/call\n", bench_permute_12());
    // printf("Permute-24:       %f cycles/call\n", bench_permute_24());
    // // printf("Permute-N(6):     %lu cycles/call\n", bench_permute_n(6));
    // // printf("Permute-N(24):    %lu cycles/call\n", bench_permute_n(24));
    return 0;
}

