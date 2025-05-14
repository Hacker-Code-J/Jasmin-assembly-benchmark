// gcc -std=c99 -O2 -Wall -Wextra -m64 -c KeccakP-1600-reference.c -o keccak_ref.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c KeccakP-1600-x86-64.s -o keccak_asm.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -c main.c   -o main.o
// gcc -m64 main.o keccak_ref.o -o keccak_test_c
// gcc -m64 -no-pie main.o keccak_asm.o -o keccak_test_asm

// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c KeccakP-1600-x86-64.s -o keccak_asm.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c main.c -o main.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c KeccakP-1600-reference.c -o keccak_ref.o
// gcc -m64 -no-pie main.o keccak_asm.o -o keccak_test_asm

// gcc -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c KeccakP-1600-AVX2.s -o keccak_avx2.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c main.c -o main.o
// gcc -mavx2 -no-pie main.o keccak_avx2.o -o keccak_test_avx2

/* REF */

/* x86_64 */

/* AVX2 */

/** Note
 * -fno-pie: This option disables position-independent executable (PIE) generation.
 *           PIE is a security feature that makes it harder for attackers to exploit vulnerabilities.
 *           By default, modern compilers generate PIE binaries, which can be more secure but may not be
 *           compatible with all code or libraries.
 * -no-pie: This option is used to create a non-PIE executable. It is the opposite of -fpie and is used
 *          when you want to create a standard executable that does not require position-independent code.
 *          This is useful when you are working with legacy code or when you need to ensure compatibility
 *          with certain environments or systems that do not support PIE.
 * -c: This option tells the compiler to compile the source files into object files without linking.
 *    It is used when you want to compile multiple source files separately and then link them together later.
 *    This is useful for modular programming, where you can compile each module separately and then link
 *    them into a final executable. It allows for better organization of code and faster compilation times.
 *    The -c option is commonly used in large projects where multiple source files are involved.
 * -o: This option specifies the output file name for the compiled object file. It allows you to control
 *     the name of the generated object file. By default, the compiler generates an object file with a
 *     name based on the source file name, but using the -o option allows you to specify a custom name.
 *     This is useful for organizing object files or when you want to avoid naming conflicts with other files.
 *     It is a common practice to use the -o option to give meaningful names to object files, especially
 *     in larger projects where multiple object files are generated.
 * -m64: This option tells the compiler to generate code for a 64-bit architecture.
 *       It is used to ensure that the generated code is compatible with 64-bit systems.
 *       This is important for performance and compatibility reasons, especially when dealing with
 *       large data structures or memory addresses.
 * -O2: This option enables a set of optimizations that improve the performance of the generated code.
 *      It is a commonly used optimization level that balances compilation time and runtime performance.
 *      The -O2 level includes various optimizations such as inlining functions, loop unrolling, and
 *      dead code elimination, among others.
 *      It is a good choice for most applications where performance is important.
 * -Wall: This option enables all compiler warnings. It is a good practice to use this option to catch
 *        potential issues in the code during compilation. It helps identify problems such as unused variables,
 *        uninitialized variables, and other common mistakes that could lead to bugs or undefined behavior.
 *        Enabling all warnings can help improve code quality and maintainability.
 * -Wextra: This option enables additional warnings that are not included in the -Wall option.
 *           It provides even more checks for potential issues in the code. Using -Wextra along with -Wall
 *           is a good practice to ensure that the code is as clean and error-free as possible.
 *           It can help catch more subtle issues that may not be covered by the standard warnings.
 *           This option is particularly useful for developers who want to maintain high code quality and
 *           avoid potential pitfalls in their code.
 * -fPIC: This option generates position-independent code (PIC), which is suitable for shared libraries.
 *        PIC allows the code to be loaded at any memory address without modification, making it more flexible
 *        for dynamic linking. It is commonly used when creating shared libraries or when the code needs to be
 *        relocatable. Using -fPIC is important for compatibility with shared libraries and dynamic linking.
 *        It is especially relevant when working with shared libraries or when the code needs to be relocatable.
 *        Using -fPIC is important for compatibility with shared libraries and dynamic linking.
 *        It is especially relevant when working with shared libraries or when the code needs to be relocatable.
 * -std=c99: This option specifies the C language standard to be used for compilation.
 *           In this case, it indicates that the C99 standard should be used. C99 introduced several new features
 *           and improvements to the C language, including support for new data types, variable-length arrays,
 *           and improved support for floating-point arithmetic. Using -std=c99 ensures that the code is compiled
 *           according to the C99 standard, which may be necessary for compatibility with certain libraries or
 *           features. It is important to specify the correct standard to ensure that the code behaves as expected
 *           and takes advantage of the features available in that standard.
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include "KeccakP-1600-SnP.h"  // declare KeccakP1600_* functions

// Compare two Keccak states
// static void compare_state(const KeccakP1600_state *a, const KeccakP1600_state *b) {
//     assert(memcmp(a->A, b->A, 200) == 0);
// }

// // Compare two byte arrays
// static void compare_bytes(const uint8_t *x, const uint8_t *y, unsigned len) {
//     assert(memcmp(x, y, len) == 0);
// }

// // 1. Test Initialize()
// static void test_initialize() {
//     KeccakP1600_state s;
//     uint8_t buf[200];

//     // initialize the (possibly complemented) lanes
//     KeccakP1600_Initialize(&s);

//     // now fetch the *logical* bytes
//     KeccakP1600_ExtractBytes(&s, buf, /*offset=*/0, /*length=*/200);

//     // those *should* all be zero
//     for (int i = 0; i < 200; i++) {
//         assert(buf[i] == 0);
//     }
// }
// // static void test_initialize() {
// //     KeccakP1600_state s;
// //     KeccakP1600_Initialize(&s);
// //     // Check all bytes zero
// //     for (int i = 0; i < 200; i++) {
// //         assert(s.A[i] == 0);
// //     }
// //     // Cross-check against a manual zero state
// //     KeccakP1600_state ref = {{0}};
// //     compare_state(&s, &ref);
// // }


// // 2. Test AddByte() and AddBytes()
// static void test_addbyte_addbytes() {
//     KeccakP1600_state s1, s2;
//     uint8_t data[8] = {0,1,2,3,4,5,6,7};
//     uint8_t out1[200], out2[200];

//     KeccakP1600_Initialize(&s1);
//     KeccakP1600_Initialize(&s2);

//     // single-byte vs AddBytes(…,1)
//     KeccakP1600_AddByte(&s1, data[3], 10);
//     KeccakP1600_AddBytes(&s2, data+3, 10, 1);

//     // extract the *logical* state
//     KeccakP1600_ExtractBytes(&s1, out1, 0, 200);
//     KeccakP1600_ExtractBytes(&s2, out2, 0, 200);
//     // now compare the two extracted buffers
//     compare_bytes(out1, out2, 200);

//     // multi-byte at offset
//     KeccakP1600_Initialize(&s1);
//     KeccakP1600_AddBytes(&s1, data, 20, 8);
//     // extract again
//     KeccakP1600_ExtractBytes(&s1, out1, 0, 200);

//     for (int i = 0; i < 8; i++) {
//         assert(out1[20 + i] == data[i]);
//     }
// }
// // static void test_addbyte_addbytes() {
// //     KeccakP1600_state s1, s2;
// //     uint8_t data[8] = {0,1,2,3,4,5,6,7};

// //     KeccakP1600_Initialize(&s1);
// //     KeccakP1600_Initialize(&s2);

// //     // single-byte vs vector AddBytes length=1
// //     KeccakP1600_AddByte(&s1, data[3], 10);
// //     KeccakP1600_AddBytes(&s2, data+3, 10, 1);
// //     compare_state(&s1, &s2);

// //     // multi-byte at offset
// //     KeccakP1600_Initialize(&s1);
// //     KeccakP1600_Initialize(&s2);
// //     KeccakP1600_AddBytes(&s1, data, 20, 8);
// //     for (int i = 0; i < 8; i++) {
// //         assert(s1.A[20 + i] == data[i]);
// //     }
// // }

// // 3. Test OverwriteBytes() and OverwriteWithZeroes()
// static void test_overwrite_bytes_zeroes() {
//     KeccakP1600_state s;
//     uint8_t pattern[16], buf[200];

//     for (int i = 0; i < 16; i++) pattern[i] = 0xA5;

//     KeccakP1600_Initialize(&s);
//     // write 16-byte pattern at offset 50 (logical state)
//     KeccakP1600_OverwriteBytes(&s, pattern, 50, 16);
//     // extract the logical full state
//     KeccakP1600_ExtractBytes(&s, buf, 0, 200);
//     // now check that buf[50..65) == pattern[]
//     assert(memcmp(buf + 50, pattern, 16) == 0);

//     // overwrite first 20 bytes with zeros
//     KeccakP1600_OverwriteWithZeroes(&s, 20);
//     KeccakP1600_ExtractBytes(&s, buf, 0, 200);
//     for (int i = 0; i < 20; i++) {
//         assert(buf[i] == 0);
//     }
// }
// // static void test_overwrite_bytes_zeroes() {
// //     KeccakP1600_state s;
// //     uint8_t pattern[16];
// //     for (int i = 0; i < 16; i++) pattern[i] = 0xA5;

// //     KeccakP1600_Initialize(&s);
// //     KeccakP1600_OverwriteBytes(&s, pattern, 50, 16);
// //     assert(memcmp(s.A + 50, pattern, 16) == 0);

// //     KeccakP1600_OverwriteWithZeroes(&s, 20);
// //     for (int i = 0; i < 20; i++) {
// //         assert(s.A[i] == 0);
// //     }
// // }

// // 4. Test Permutations
// static void test_permute_rounds() {
//     KeccakP1600_state s1, s2;
//     uint8_t out1[200], out2[200];

//     // 12-round vs dedicated
//     KeccakP1600_Initialize(&s1);
//     KeccakP1600_Initialize(&s2);
//     // inject one logical non-zero byte via Overwrite
//     uint8_t one = 1;
//     KeccakP1600_OverwriteBytes(&s1, &one, 0, 1);
//     KeccakP1600_OverwriteBytes(&s2, &one, 0, 1);
//     KeccakP1600_Permute_Nrounds(&s1, 12);
//     KeccakP1600_Permute_12rounds(&s2);
//     KeccakP1600_ExtractBytes(&s1, out1, 0, 200);
//     KeccakP1600_ExtractBytes(&s2, out2, 0, 200);
//     compare_bytes(out1, out2, 200);

//     // 24-round vs dedicated
//     KeccakP1600_Initialize(&s1);
//     KeccakP1600_Initialize(&s2);
//     uint8_t two = 2;
//     KeccakP1600_OverwriteBytes(&s1, &two, 0, 1);
//     KeccakP1600_OverwriteBytes(&s2, &two, 0, 1);
//     KeccakP1600_Permute_Nrounds(&s1, 24);
//     KeccakP1600_Permute_24rounds(&s2);
//     KeccakP1600_ExtractBytes(&s1, out1, 0, 200);
//     KeccakP1600_ExtractBytes(&s2, out2, 0, 200);
//     compare_bytes(out1, out2, 200);
// }
// // static void test_permute_rounds() {
// //     KeccakP1600_state s1, s2;

// //     // arbitrary 12-round vs dedicated 12-round
// //     KeccakP1600_Initialize(&s1);
// //     KeccakP1600_Initialize(&s2);
// //     s1.A[0] = s2.A[0] = 0x01;  // inject non-zero
// //     KeccakP1600_Permute_Nrounds(&s1, 12);
// //     KeccakP1600_Permute_12rounds(&s2);
// //     compare_state(&s1, &s2);

// //     // arbitrary 24-round vs dedicated 24-round
// //     KeccakP1600_Initialize(&s1);
// //     KeccakP1600_Initialize(&s2);
// //     s1.A[0] = s2.A[0] = 0x02;
// //     KeccakP1600_Permute_Nrounds(&s1, 24);
// //     KeccakP1600_Permute_24rounds(&s2);
// //     compare_state(&s1, &s2);
// // }

// // 5. Test ExtractBytes() and ExtractAndAddBytes()
// static void test_extract_and_add() {
//     KeccakP1600_state s;
//     uint8_t init[32], in[32], out[32], buf[200];

//     for (int i = 0; i < 32; i++) {
//         init[i] = (uint8_t)(i + 1);
//         in[i]   = (uint8_t)i;
//     }

//     KeccakP1600_Initialize(&s);
//     // set logical state bytes 0..31 to init[]
//     KeccakP1600_OverwriteBytes(&s, init, 0, 32);

//     // test ExtractBytes: should reproduce init[]
//     KeccakP1600_ExtractBytes(&s, buf, 0, 32);
//     assert(memcmp(buf, init, 32) == 0);

//     // test ExtractAndAddBytes: out2[i] = init[i] ^ in[i]
//     KeccakP1600_ExtractAndAddBytes(&s, in, out, 0, 32);
//     for (int i = 0; i < 32; i++) {
//         assert(out[i] == (uint8_t)(init[i] ^ in[i]));
//     }
// }
// static void test_extract_and_add() {
//     KeccakP1600_state s;
//     uint8_t out1[32], out2[32], in[32];

//     for (int i = 0; i < 32; i++) in[i] = i;

//     KeccakP1600_Initialize(&s);
//     // fill state
//     for (int i = 0; i < 32; i++) s.A[i] = i + 1;

//     // test ExtractBytes
//     KeccakP1600_ExtractBytes(&s, out1, 0, 32);
//     assert(memcmp(out1, s.A, 32) == 0);

//     // test ExtractAndAddBytes
//     KeccakP1600_ExtractAndAddBytes(&s, in, out2, 0, 32);
//     for (int i = 0; i < 32; i++) {
//         assert(out2[i] == (uint8_t)(in[i] ^ s.A[i]));
//     }
// }

#ifdef JASMIN

#else
int sha3(uint8_t *hash, const uint8_t *input, uint64_t input_length) {
    KeccakP1600_plain8_state state;
    unsigned int offset = 0;

    // Initialize Keccak state
    KeccakP1600_Initialize(&state);

    // Absorb the input
    for (unsigned int i = 0; i < input_length; i++) {
        KeccakP1600_AddByte(&state, input[i], offset);
        offset = (offset + 1) % 200; // Keccak state is 200 bytes
    }

    // Apply the 24 rounds of Keccak permutation
    KeccakP1600_Permute_24rounds(&state);

    // Extract the hash
    KeccakP1600_ExtractBytes(&state, hash, 0, 32); // For SHA3-256, we extract 32 bytes
    // KeccakP1600_ExtractBytes(&state, hash, 0, 48); // For SHA3-384, we extract 48 bytes
    // KeccakP1600_ExtractBytes(&state, hash, 0, 64); // For SHA3-512, we extract 64 bytes

    return 0; // Successful execution
}
#endif

// Function to compare two byte arrays (hashes)
int compare_hashes(uint8_t *expected_hash, uint8_t *computed_hash, size_t length) {
    for (size_t i = 0; i < length; i++) {
        if (expected_hash[i] != computed_hash[i]) {
            return 0;  // Hashes do not match
        }
    }
    return 1;  // Hashes match
}

// SHA3-256 Test Vector from NIST
void test_sha3_256() {
    // Example test vector 1 (from NIST)
    uint8_t input[] = {
        0x61, 0x62, 0x63  // "abc" in ASCII
    };
    uint8_t expected_hash[32] = {
        0xA7, 0xA4, 0xF4, 0xE6, 0x26, 0x15, 0x64, 0x42, 0xA2, 0x6D,
        0x16, 0x88, 0xD4, 0x77, 0xB3, 0x06, 0x99, 0xE0, 0x19, 0xF1,
        0x5F, 0x92, 0x57, 0xD6, 0x72, 0xD7, 0x31, 0x42, 0xE3, 0x5E,
        0x56, 0x6F
    };

    uint8_t computed_hash[32];

    // Call your sha3 function to compute the hash
    sha3(computed_hash, input, sizeof(input));

    // Compare the computed hash to the expected hash
    if (compare_hashes(expected_hash, computed_hash, sizeof(expected_hash))) {
        printf("SHA3-256 test passed!\n");
    } else {
        printf("SHA3-256 test failed!\n");
    }
}

int main(void) {
    test_sha3_256();
    // printf("Testing KeccakP1600 reference implementation...\n");
    // test_initialize();
    // printf("  [PASS] Initialize\n");
    // test_addbyte_addbytes();
    // printf("  [PASS] AddByte / AddBytes\n");
    // test_overwrite_bytes_zeroes();
    // printf("  [PASS] OverwriteBytes / OverwriteWithZeroes\n");
    // test_permute_rounds();
    // printf("  [PASS] Permute_Nrounds, 12rounds, 24rounds\n");
    // test_extract_and_add();
    // printf("  [PASS] ExtractBytes / ExtractAndAddBytes\n");
    // printf("All tests passed.\n");

    return 0;
}
