/* FILE: src/blockcipher/ossl_aes_ctr.c */
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

/*
 * NOTE: the IV/counter CTR mode is big-endian.  The code itself is
 * endian-neutral.
 */

/* increment counter (128-bit int) by 1 */
static void ctr128_inc(u8 *counter)
{
    u32 n = 16, c = 1;

    do {
        --n;
        c += counter[n];
        counter[n] = (u8)c;
        c >>= 8;
    } while (n);
}

/*
 * The input encrypted as though 128bit counter mode is being used.  The
 * extra state information to record how much of the 128bit block we have
 * used is contained in *num, and the encrypted counter is kept in
 * ecount_buf.  Both *num and ecount_buf must be initialised with zeros
 * before the first call to CRYPTO_ctr128_encrypt(). This algorithm assumes
 * that the counter is in the x lower bits of the IV (ivec), and that the
 * application has full control over overflow and the rest of the IV.  This
 * implementation takes NO responsibility for checking that the counter
 * doesn't overflow into the rest of the IV when incremented.
 */
void CRYPTO_ctr128_encrypt(const u8 *in, u8 *out, size_t len, const void *key,
    u8 ivec[16], u8 ecount_buf[16], u32 *num, block128_f block) {
    u32 n;
    size_t l = 0;

    n = *num;

    while (l < len) {
        if (n == 0) {
            (*block) (ivec, ecount_buf, key);
            ctr128_inc(ivec);
        }
        out[l] = in[l] ^ ecount_buf[n];
        ++l;
        n = (n + 1) % 16;
    }

    *num = n;
}

/* increment upper 96 bits of 128-bit counter by 1 */
static void ctr96_inc(u8 *counter)
{
    u32 n = 12, c = 1;

    do {
        --n;
        c += counter[n];
        counter[n] = (u8)c;
        c >>= 8;
    } while (n);
}

void CRYPTO_ctr128_encrypt_ctr32(const u8 *in, u8 *out, size_t len, const void *key, 
    u8 ivec[16], u8 ecount_buf[16], u32 *num, ctr128_f func) {
    u32 n, ctr32;

   n = *num;

    while (n && len) {
        *(out++) = *(in++) ^ ecount_buf[n];
        --len;
        n = (n + 1) % 16;
    }

    ctr32 = GETU32(ivec + 12);
    while (len >= 16) {
        size_t blocks = len / 16;
        /*
         * 1<<28 is just a not-so-small yet not-so-large number...
         * Below condition is practically never met, but it has to
         * be checked for code correctness.
         */
        if (sizeof(size_t) > sizeof(u32) && blocks > (1U << 28))
            blocks = (1U << 28);
        /*
         * As (*func) operates on 32-bit counter, caller
         * has to handle overflow. 'if' below detects the
         * overflow, which is then handled by limiting the
         * amount of blocks to the exact overflow point...
         */
        ctr32 += (u32)blocks;
        if (ctr32 < blocks) {
            blocks -= ctr32;
            ctr32 = 0;
        }
        (*func) (in, out, blocks, key, ivec);
        /* (*ctr) does not update ivec, caller does: */
        PUTU32(ivec + 12, ctr32);
        /* ... overflow was detected, propagate carry. */
        if (ctr32 == 0)
            ctr96_inc(ivec);
        blocks *= 16;
        len -= blocks;
        out += blocks;
        in += blocks;
    }
    if (len) {
        memset(ecount_buf, 0, 16);
        (*func) (ecount_buf, ecount_buf, 1, key, ivec);
        ++ctr32;
        PUTU32(ivec + 12, ctr32);
        if (ctr32 == 0)
            ctr96_inc(ivec);
        while (len--) {
            out[n] = in[n] ^ ecount_buf[n];
            ++n;
        }
    }

    *num = n;
}