/* FILE: include/openssl/ossl_aes.h */
#include "../jab_setup.h"
/*
 * Copyright 2002-2020 The OpenSSL Project Authors. All Rights Reserved.
 *
 * Licensed under the Apache License 2.0 (the "License").  You may not use
 * this file except in compliance with the License.  You can obtain a copy
 * in the file LICENSE in the source distribution or at
 * https://www.openssl.org/source/license.html
 */

#ifndef OSSL_AES_H
#define OSSL_AES_H

#define AES_BLOCK_SIZE  16

#define AES_ENCRYPT     1
#define AES_DECRYPT     0

#define AES_MAXNR       14

#define GETU32(pt) (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] <<  8) ^ ((u32)(pt)[3]))
#define PUTU32(ct, st) { (ct)[0] = (u8)((st) >> 24); (ct)[1] = (u8)((st) >> 16); (ct)[2] = (u8)((st) >>  8); (ct)[3] = (u8)(st); }

/* This should be a hidden type, but EVP requires that the size be known */
struct aes_key_st {
    u32 rd_key[4 * (AES_MAXNR + 1)];
    int rounds;
};
typedef struct aes_key_st AES_KEY;

int AES_set_encrypt_key(const u8 *userKey, const int bits, AES_KEY *key);
int AES_set_decrypt_key(const u8 *userKey, const int bits, AES_KEY *key);
void AES_encrypt(const u8 *in, u8 *out, const AES_KEY *key);
void AES_decrypt(const u8 *in, u8 *out, const AES_KEY *key);

#endif /* OSSL_AES_H */