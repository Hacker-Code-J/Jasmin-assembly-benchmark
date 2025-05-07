// #include <oqs/rand.h>
#include "jade_kem_keyber.h"
#include <stdlib.h>
#include <time.h>

int libjade_kyber512_ref_keypair(uint8_t *public_key, uint8_t *secret_key) {
    srand(time(NULL));
    uint8_t keypair_coins[JADE_KEM_kyber_kyber512_amd64_ref_KEYPAIRCOINBYTES];
    // OQS_randombytes(keypair_coins, JADE_KEM_kyber_kyber512_amd64_ref_KEYPAIRCOINBYTES/2);
    for (int i = 0; i < JADE_KEM_kyber_kyber512_amd64_ref_KEYPAIRCOINBYTES / 2; i++) {
        keypair_coins[i] = rand() % 256;
    }
    // OQS_randombytes((uint8_t *)(keypair_coins + (JADE_KEM_kyber_kyber512_amd64_ref_KEYPAIRCOINBYTES/2)), JADE_KEM_kyber_kyber512_amd64_ref_KEYPAIRCOINBYTES/2);
    return jade_kem_kyber_kyber512_amd64_ref_keypair_derand(public_key, secret_key, keypair_coins);
}

int libjade_kyber512_ref_enc(uint8_t *ciphertext, uint8_t *shared_secret, const uint8_t *public_key) {
    srand(time(NULL));
    uint8_t enc_coins[JADE_KEM_kyber_kyber512_amd64_ref_ENCCOINBYTES];
    for (int i = 0; i < JADE_KEM_kyber_kyber512_amd64_ref_ENCCOINBYTES; i++) {
        enc_coins[i] = rand() % 256;
    }
    // OQS_randombytes(enc_coins, JADE_KEM_kyber_kyber512_amd64_ref_ENCCOINBYTES);
    return jade_kem_kyber_kyber512_amd64_ref_enc_derand(ciphertext, shared_secret, public_key, enc_coins);
}

int libjade_kyber512_ref_dec(uint8_t *shared_secret, const uint8_t *ciphertext, const uint8_t *secret_key) {
    return jade_kem_kyber_kyber512_amd64_ref_dec(shared_secret, ciphertext, secret_key);
}
