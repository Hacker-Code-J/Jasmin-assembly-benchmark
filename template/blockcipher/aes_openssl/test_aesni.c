/*
 * 1) assemble your .S file (make sure -maes -mssse3 are enabled)
 * 2) compile the C test
 * 3) link them together
 * 4) run it
 */
// gcc -c -O2 -maes -mssse3 test_aesni.c -o test_aesni.o
// gcc -O2 -maes -mssse3 aesni.o test_aesni.o -lcrypto -o test_aesni
// ./test_aesni

#include <stdio.h>
#include <string.h>
#include "aesni.h"

/*
 * turn off all OpenSSL‐style capability checks:
 * OPENSSL_ia32cap_P is normally an array of at least 4 unsigned‐longs.
 */
unsigned long OPENSSL_ia32cap_P[1] = { 0 };

/* A single 128-bit block test vector (AES-ECB):
 *   PT =  00112233445566778899aabbccddeeff
 *   KEY = 000102030405060708090a0b0c0d0e0f
 *   CT =  69c4e0d86a7b0430d8cdb78070b4c55a
 */
static const uint8_t PT[16] = {
    0x00,0x11,0x22,0x33, 0x44,0x55,0x66,0x77,
    0x88,0x99,0xaa,0xbb, 0xcc,0xdd,0xee,0xff
};
static const uint8_t KEY[16] = {
    0x00,0x01,0x02,0x03, 0x04,0x05,0x06,0x07,
    0x08,0x09,0x0a,0x0b, 0x0c,0x0d,0x0e,0x0f
};
static const uint8_t EXPECTED_CT[16] = {
    0x69,0xc4,0xe0,0xd8, 0x6a,0x7b,0x04,0x30,
    0xd8,0xcd,0xb7,0x80, 0x70,0xb4,0xc5,0x5a
};

int main(void) {
    aesni_key_schedule ks_enc, ks_dec;
    uint8_t ct[16], pt2[16];
    int rc;

    /* 1) set up encryption key schedule */
    rc = aesni_set_encrypt_key(KEY, 128, ks_enc);
    if (rc) {
        fprintf(stderr, "aesni_set_encrypt_key failed (%d)\n", rc);
        return 1;
    }

    /* 2) encrypt one block */
    aesni_encrypt(PT, ct, ks_enc);

    /* 3) check against known cipher-text */
    if (memcmp(ct, EXPECTED_CT, 16) != 0) {
        fprintf(stderr, "ENCRYPTION mismatch!\n");
        return 2;
    }

    /* 4) set up decryption key schedule */
    rc = aesni_set_decrypt_key(KEY, 128, ks_dec);
    if (rc) {
        fprintf(stderr, "aesni_set_decrypt_key failed (%d)\n", rc);
        return 3;
    }

    /* 5) decrypt and verify we get back the plain-text */
    aesni_decrypt(ct, pt2, ks_dec);
    if (memcmp(pt2, PT, 16) != 0) {
        fprintf(stderr, "DECRYPTION mismatch!\n");
        return 4;
    }

    puts("AESNI test passed!");
    return 0;
}
