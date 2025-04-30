// tests/test_ossl_aes.c
#include "../include/jab_setup.h"   // your typedefs for u8, size_t, etc.
#include "../include//openssl/ossl_aes.h"    // your renamed aes header
#include "../include/openssl/ossl_mode.h" 
#include "../include/openssl/ossl_aesni.h"

// ----------- ECB test (from before) -----------
static int test_ecb(void) {
    static const u8 key_data[16] = {
        0x2b,0x7e,0x15,0x16, 0x28,0xae,0xd2,0xa6,
        0xab,0xf7,0x15,0x88, 0x09,0xcf,0x4f,0x3c
    };
    static const u8 pt[16] = {
        0x6b,0xc1,0xbe,0xe2, 0x2e,0x40,0x9f,0x96,
        0xe9,0x3d,0x7e,0x11, 0x73,0x93,0x17,0x2a
    };
    static const u8 ct_exp[16] = {
        0x3a,0xd7,0x7b,0xb4, 0x0d,0x7a,0x36,0x60,
        0xa8,0x9e,0xca,0xf3, 0x24,0x66,0xef,0x97
    };

    AES_KEY key;
    u8 out[16];

    if (AES_set_encrypt_key(key_data,128,&key) < 0) {
        fprintf(stderr,"ECB: set_encrypt_key failed\n");
        return 1;
    }
    AES_encrypt(pt, out, &key);
    if (memcmp(out, ct_exp,16)!=0) {
        fprintf(stderr,"FAIL: AES-128 ECB encrypt\n");
        return 1;
    }
    if (AES_set_decrypt_key(key_data,128,&key) < 0) {
        fprintf(stderr,"ECB: set_decrypt_key failed\n");
        return 1;
    }
    AES_decrypt(ct_exp, out, &key);
    if (memcmp(out, pt,16)!=0) {
        fprintf(stderr,"FAIL: AES-128 ECB decrypt\n");
        return 1;
    }

    printf("PASS: AES-128 ECB\n");
    return 0;
}

// ----------- CBC test -----------
static int test_cbc(void) {
    static const u8 key[16] = {
        0x2b,0x7e,0x15,0x16, 0x28,0xae,0xd2,0xa6,
        0xab,0xf7,0x15,0x88, 0x09,0xcf,0x4f,0x3c
    };
    static const u8 iv[16] = {
        0x00,0x01,0x02,0x03, 0x04,0x05,0x06,0x07,
        0x08,0x09,0x0a,0x0b, 0x0c,0x0d,0x0e,0x0f
    };
    static const u8 pt2[32] = {
        0x6b,0xc1,0xbe,0xe2, 0x2e,0x40,0x9f,0x96,
        0xe9,0x3d,0x7e,0x11, 0x73,0x93,0x17,0x2a,
        0xae,0x2d,0x8a,0x57, 0x1e,0x03,0xac,0x9c,
        0x9e,0xb7,0x6f,0xac, 0x45,0xaf,0x8e,0x51
    };
    static const u8 ct2_exp[32] = {
        0x76,0x49,0xab,0xac, 0x81,0x19,0xb2,0x46,
        0xce,0xe9,0x8e,0x9b, 0x12,0xe9,0x19,0x7d,
        0x50,0x86,0xcb,0x9b, 0x50,0x72,0x19,0xee,
        0x95,0xdb,0x11,0x3a, 0x91,0x76,0x78,0xb2
    };

    AES_KEY key_ctx;
    u8 out[32], iv_copy[16];
    memcpy(iv_copy, iv, 16);

    if (AES_set_encrypt_key(key,128,&key_ctx)<0) {
        fprintf(stderr,"CBC: set_encrypt_key failed\n");
        return 1;
    }
    AES_cbc_encrypt(pt2, out, sizeof(pt2), &key_ctx, iv_copy, AES_ENCRYPT);
    if (memcmp(out, ct2_exp,32)!=0) {
        fprintf(stderr,"FAIL: AES-128 CBC encrypt\n");
        return 1;
    }

    memcpy(iv_copy, iv, 16);
    if (AES_set_decrypt_key(key,128,&key_ctx)<0) {
        fprintf(stderr,"CBC: set_decrypt_key failed\n");
        return 1;
    }
    AES_cbc_encrypt(ct2_exp, out, sizeof(pt2), &key_ctx, iv_copy, AES_DECRYPT);
    if (memcmp(out, pt2,32)!=0) {
        fprintf(stderr,"FAIL: AES-128 CBC decrypt\n");
        return 1;
    }

    printf("PASS: AES-128 CBC\n");
    return 0;
}

// // ----------- CTR test -----------
// static int test_ctr(void) {
//     static const u8 key[16] = {
//         0x2b,0x7e,0x15,0x16, 0x28,0xae,0xd2,0xa6,
//         0xab,0xf7,0x15,0x88, 0x09,0xcf,0x4f,0x3c
//     };
//     static const u8 nonce[16] = {
//         0x00,0x01,0x02,0x03, 0x04,0x05,0x06,0x07,
//         0x08,0x09,0x0a,0x0b, 0x0c,0x0d,0x0e,0x0f
//     };
//     static const u8 pt1[16] = {
//         0x6b,0xc1,0xbe,0xe2, 0x2e,0x40,0x9f,0x96,
//         0xe9,0x3d,0x7e,0x11,0x73,0x93,0x17,0x2a
//     };
//     static const u8 ct1_exp[16] = {
//         0x87,0x4d,0x61,0x91, 0xb6,0x20,0xe3,0x26,
//         0x1b,0xef,0x68,0x64, 0x99,0x0d,0xb6,0xce
//     };

//     AES_KEY key_ctx;
//     u8 out[16], ivec[16], ecount[AES_BLOCK_SIZE];
//     unsigned int num = 0;
//     memcpy(ivec, nonce, 16);
//     memset(ecount, 0, AES_BLOCK_SIZE);

//     if (AES_set_encrypt_key(key,128,&key_ctx)<0) {
//         fprintf(stderr,"CTR: set_encrypt_key failed\n");
//         return 1;
//     }
//     CRYPTO_ctr128_encrypt(pt1, out, sizeof(pt1), &key_ctx, ivec, ecount, &num);
//     if (memcmp(out, ct1_exp,16)!=0) {
//         fprintf(stderr,"FAIL: AES-128 CTR encrypt\n");
//         return 1;
//     }

//     printf("PASS: AES-128 CTR\n");
//     return 0;
// }

int main(void) {
    int failures = 0;
    failures += test_ecb();
    failures += test_cbc();
    // failures += test_ctr();

    if (failures==0) {
        printf("All tests passed.\n");
        return 0;
    } else {
        printf("%d test(s) failed.\n", failures);
        return 1;
    }
}
