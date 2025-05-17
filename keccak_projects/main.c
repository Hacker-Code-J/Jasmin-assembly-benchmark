/* REF */
// gcc -std=c99 -O2 -Wall -Wextra -m64 -c KeccakP-1600-reference.c -o keccak_ref.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -c main.c   -o main.o
// gcc -m64 main.o keccak_ref.o -o keccak_test_c

/* x86_64 */
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c KeccakP-1600-x86-64.s -o keccak_asm.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c main.c -o main.o
// gcc -m64 -no-pie main.o keccak_asm.o -o keccak_test_asm

/* AVX2 */
// gcc -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c KeccakP-1600-AVX2.s -o keccak_avx2.o
// gcc -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c main.c -o main.o
// gcc -mavx2 -no-pie main.o keccak_avx2.o -o keccak_test_avx2

/* Jasmin-x86_64 */
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c sha3_256_ref.s -o sha3_256_ref_jasmin.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c sha3_384_ref.s -o sha3_384_ref_jasmin.o
// gcc -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c sha3_512_ref.s -o sha3_512_ref_jasmin.o
// gcc -DJASMIN -std=c99 -O2 -Wall -Wextra -m64 -fno-pie -c main.c -o main.o
// gcc -m64 -no-pie main.o sha3_256_ref_jasmin.o -o test_sha3_256_ref_jasmin

/* Jasmin-AVX2 */
// gcc -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c sha3_256_avx2.s -o sha3_256_avx2_jasmin.o
// gcc -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c sha3_384_avx2.s -o sha3_384_avx2_jasmin.o
// gcc -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c sha3_512_avx2.s -o sha3_512_avx2_jasmin.o
// gcc -DJASMIN -std=c99 -O2 -Wall -Wextra -mavx2 -fno-pie -c main.c -o main.o
// gcc -mavx2 -no-pie main.o sha3_256_avx2_jasmin.o -o test_sha3_256_avx2_jasmin

/* MAIN */
// gcc -O3 -march=native -o test_c_xkcp main.c KeccakP-1600-reference.o
// gcc -O3 -march=native -no-pie -o test_x86_64_xkcp main.c KeccakP-1600-x86-64.o
// gcc -O3 -march=native -mavx2 -o test_avx2_xkcp main.c KeccakP-1600-AVX2.o
// gcc -DJASMIN -O3 -o test_x86_64_libjade main.c sha3_256_ref_jasmin.o sha3_384_ref_jasmin.o sha3_512_ref_jasmin.o
// gcc -DJASMIN -O3 -mavx2 -o test_avx2_libjade main.c sha3_256_avx2_jasmin.o sha3_384_avx2_jasmin.o sha3_512_avx2_jasmin.o

/* DUMP (x86_64) */
// as -o KeccakP-1600-x86-64.o KeccakP-1600-x86-64.s
// gcc -O3 -march=native -o sha3_256.o -c main_sha3_256.c
// gcc -O3 -march=native -no-pie -flto -funroll-loops -o dump_x86_64_xkcp main.c sha3_256.o KeccakP-1600-x86-64.o
// as -o sha3_256_ref_jasmin.o sha3_256_ref.s
// as -o sha3_384_ref_jasmin.o sha3_384_ref.s
// as -o sha3_512_ref_jasmin.o sha3_512_ref.s
// gcc -DJASMIN -O3 -funroll-loops -flto -o dump_x86_64_libjade main.c sha3_256_ref_jasmin.o

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
extern int jade_hash_sha3_256_amd64(uint8_t *hash, const uint8_t *input, uint64_t input_length);
#else
extern int sha3(uint8_t *hash, const uint8_t *input, uint64_t input_length);
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
//     KeccakP1600_ExtractBytes(&state, hash, 0, 32); // For SHA3-256, we extract 32 bytes

//     // // Debug: print the final hash
//     // printf("Extracted hash: ");
//     // for (int i = 0; i < 32; i++) {
//     //     printf("%02x", hash[i]);
//     // }
//     // printf("\n");

//     return 0; // Successful execution
// }
#endif

// Function to compare two byte arrays
int compare_bytes(const uint8_t *a, const uint8_t *b, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            return 1;  // They are different
        }
    }
    return 0;  // They are the same
}

// Function to convert hex string to bytes
int hex_to_bytes(const char* hex, uint8_t* bytes, size_t len) {
    for (size_t i = 0; i < len; i++) {
        sscanf(hex + 2*i, "%2hhx", &bytes[i]);
    }
    return 0;
}

// Test case structure
typedef struct {
    uint64_t length;
    const char *msg_hex;
    const char *md_hex;
} TestVector;

// Example test vectors (your provided vectors)
TestVector test_vectors[] = {
    { 0, "00", "a7ffc6f8bf1ed76651c14756a061d662f580ff4de43b49fa82d80a4b80f8434a" },
    { 8, "e9", "f0d04dd1e6cfc29a4460d521796852f25d9ef8d28b44ee91ff5b759d72c1e6d6" },
    { 16, "d477", "94279e8f5ccdf6e17f292b59698ab4e614dfe696a46c46da78305fc6a3146ab7" },
    { 24, "b053fa", "9d0ff086cd0ec06a682c51c094dc73abdc492004292344bd41b82a60498ccfdb" },
    { 32, "e7372105", "3a42b68ab079f28c4ca3c752296f279006c4fe78b1eb79d989777f051e4046ae" },
    { 40, "0296f2c40a", "53a018937221081d09ed0497377e32a1fa724025dfdc1871fa503d545df4b40d" },
    { 48, "e6fd42037f80", "2294f8d3834f24aa9037c431f8c233a66a57b23fa3de10530bbb6911f6e1850f" },
    { 56, "37b442385e0538", "cfa55031e716bbd7a83f2157513099e229a88891bb899d9ccd317191819998f8" },
    { 64, "8bca931c8a132d2f", "dbb8be5dec1d715bd117b24566dc3f24f2cc0c799795d0638d9537481ef1e03e" },
    { 72, "fb8dfa3a132f9813ac", "fd09b3501888445ffc8c3bb95d106440ceee469415fce1474743273094306e2e" },
    { 80, "71fbacdbf8541779c24a", "cc4e5a216b01f987f24ab9cad5eb196e89d32ed4aac85acb727e18e40ceef00e" },
    { 88, "7e8f1fd1882e4a7c49e674", "79bef78c78aa71e11a3375394c2562037cd0f82a033b48a6cc932cc43358fd9e" },
    { 96, "5c56a6b18c39e66e1b7a993a", "b697556cb30d6df448ee38b973cb6942559de4c2567b1556240188c55ec0841c" },
    { 104, "9c76ca5b6f8d1212d8e6896ad8", "69dfc3a25865f3535f18b4a7bd9c0c69d78455f1fc1f4bf4e29fc82bf32818ec" },
    { 112, "687ff7485b7eb51fe208f6ff9a1b", "fe7e68ae3e1a91944e4d1d2146d9360e5333c099a256f3711edc372bc6eeb226" },
    { 120, "4149f41be1d265e668c536b85dde41", "229a7702448c640f55dafed08a52aa0b1139657ba9fc4c5eb8587e174ecd9b92" },
    { 128, "d83c721ee51b060c5a41438a8221e040", "b87d9e4722edd3918729ded9a6d03af8256998ee088a1ae662ef4bcaff142a96" },
    { 136, "266e8cbd3e73d80df2a49cfdaf0dc39cd1", "6c2de3c95900a1bcec6bd4ca780056af4acf3aa36ee640474b6e870187f59361" },
    { 144, "a1d7ce5104eb25d6131bb8f66e1fb13f3523", "ee9062f39720b821b88be5e64621d7e0ca026a9fe7248d78150b14bdbaa40bed" },
    { 152, "d751ccd2cd65f27db539176920a70057a08a6b", "7aaca80dbeb8dc3677d18b84795985463650d72f2543e0ec709c9e70b8cd7b79" },
    { 160, "b32dec58865ab74614ea982efb93c08d9acb1bb0", "6a12e535dbfddab6d374058d92338e760b1a211451a6c09be9b61ee22f3bb467" }
};

// Run the tests
void sha3_tests() {
    uint8_t computed_hash[32]; // SHA3-256 output length
    size_t num_tests = sizeof(test_vectors) / sizeof(test_vectors[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        printf("Running test %zu\n", i + 1);
        
        // Get the current test vector
        TestVector test = test_vectors[i];
        
        // Convert the message and expected hash from hex to bytes
        uint8_t message[test.length];
        uint8_t expected_hash[32];
        
        hex_to_bytes(test.msg_hex, message, test.length);
        hex_to_bytes(test.md_hex, expected_hash, 32);
        
        // Compute the SHA3 hash
#ifdef JASMIN
        int result = jade_hash_sha3_256_amd64(computed_hash, message, test.length);
#else
        int result = sha3(computed_hash, message, test.length);
#endif        
        // Compare the computed hash with the expected hash
        if (result == 0 && compare_bytes(computed_hash, expected_hash, 32) == 0) {
            printf("Test %zu PASSED\n", i + 1);
        } else {
            printf("Test %zu FAILED\n", i + 1);
            printf("Expected hash: ");
            for (int j = 0; j < 32; j++) {
                printf("%02x", expected_hash[j]);
            }
            printf("\nComputed hash: ");
            for (int j = 0; j < 32; j++) {
                printf("%02x", computed_hash[j]);
            }
            printf("\n");
        }
    }
}
int main(void) {
//     uint8_t input[] = { 0x00 }; // Test input message
//     uint8_t expected_hash[] = { 
//         0xa7, 0xff, 0x6f, 0x8b, 0xf1, 0xed, 0x76, 0x65, 
//         0x1c, 0x14, 0x75, 0x6a, 0x06, 0x1d, 0x66, 0x2f, 
//         0x58, 0x0f, 0xf4, 0xde, 0x43, 0xb4, 0x9f, 0xa8, 
//         0x2d, 0x80, 0xa4, 0xb8, 0x0f, 0x84, 0x34, 0xa0 
//     }; // Expected output for SHA3-256

//     uint8_t hash[32]; // 32 bytes for SHA3-256

// #ifdef JASMIN
//     jade_hash_sha3_256_amd64(hash, input, sizeof(input));
// #else
//     sha3(hash, input, sizeof(input));
// #endif  
//     // Compare the output hash with the expected hash
//     if (memcmp(hash, expected_hash, 32) == 0) {
//         printf("SHA3-256 test passed.\n");
//     } else {
//         printf("SHA3-256 test failed.\n");
//         // Output the computed hash for debugging purposes
//         printf("Computed hash: ");
//         for (int i = 0; i < 32; i++) {
//             printf("%02x", hash[i]);
//         }
//         printf("\n");
//         printf("Expected hash: ");
//         for (int i = 0; i < 32; i++) {
//             printf("%02x", expected_hash[i]);
//         }
//         printf("\n");
//     }

    sha3_tests();

    // ========== TESTING ========== //
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
