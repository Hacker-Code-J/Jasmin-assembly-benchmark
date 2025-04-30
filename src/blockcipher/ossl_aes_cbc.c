/* FILE: src/blockcipher/ossl_aes_cbc.c */
/*
 * Copyright 2002-2020 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */
 #include "../../include/jab_setup.h"
 #include "../../include/openssl/ossl_aes.h"
 #include "../../include/openssl/ossl_mode.h"

 void AES_cbc_encrypt(const u8 *in, u8 *out, size_t len, const AES_KEY *key, u8 *ivec, const int enc) {
    if (enc)
    CRYPTO_cbc128_encrypt(in, out, len, key, ivec,
                (block128_f) AES_encrypt);
    else
    CRYPTO_cbc128_decrypt(in, out, len, key, ivec,
                (block128_f) AES_decrypt);
}

void CRYPTO_cbc128_encrypt(const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], block128_f block) {
    size_t n;
    const u8 *iv = ivec;

    if (len == 0)
        return;

    while (len) {
        for (n = 0; n < 16 && n < len; ++n)
            out[n] = in[n] ^ iv[n];
        for (; n < 16; ++n)
            out[n] = iv[n];
        (*block) (out, out, key);
        iv = out;
        if (len <= 16)
            break;
        len -= 16;
        in += 16;
        out += 16;
    }
    if (ivec != iv)
        memcpy(ivec, iv, 16);
}

void CRYPTO_cbc128_decrypt(const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], block128_f block) {
    size_t n;
    union {
        size_t t[16 / sizeof(size_t)];
        u8 c[16];
    } tmp;

    if (len == 0)
        return;

    while (len) {
        u8 c;
        (*block) (in, tmp.c, key);
        for (n = 0; n < 16 && n < len; ++n) {
            c = in[n];
            out[n] = tmp.c[n] ^ ivec[n];
            ivec[n] = c;
        }
        if (len <= 16) {
            for (; n < 16; ++n)
                ivec[n] = in[n];
            break;
        }
        len -= 16;
        in += 16;
        out += 16;
    }
}
