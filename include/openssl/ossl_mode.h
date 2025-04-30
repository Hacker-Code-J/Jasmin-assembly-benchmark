/* FILE: include/openssl/ossl_mode.h */
#include "../jab_setup.h"
#include "ossl_aes.h"
/*
 * Copyright 2008-2016 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

typedef void (*block128_f) (const u8 in[16], u8 out[16], const void *key);
typedef void (*cbc128_f) (const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], int enc);
typedef void (*ecb128_f) (const u8 *in, u8 *out, size_t len, const void *key, int enc);
typedef void (*ctr128_f) (const u8 *in, u8 *out, size_t blocks, const void *key, const u8 ivec[16]);

void AES_cbc_encrypt(const u8 *in, u8 *out, size_t length, const AES_KEY *key, u8 *ivec, const int enc);

void CRYPTO_cbc128_encrypt(const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], block128_f block);
void CRYPTO_cbc128_decrypt(const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], block128_f block);

void CRYPTO_ctr128_encrypt(const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], 
    u8 ecount_buf[16], u32 *num, block128_f block);

void CRYPTO_ctr128_encrypt_ctr32(const u8 *in, u8 *out, size_t len, const void *key, u8 ivec[16], 
    u8 ecount_buf[16], u32 *num, ctr128_f ctr);