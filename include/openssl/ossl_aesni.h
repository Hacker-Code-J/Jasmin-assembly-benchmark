#include "../jab_setup.h"

#ifndef AESNI_H
#define AESNI_H

/* keySchedule needs room for 15 round-keys of 16 bytes each = 240 bytes */
typedef u8 aesni_key_schedule[240];

/* defined in your .S file: */
int  aesni_set_encrypt_key(const u8 *userKey, int bits, aesni_key_schedule ks);
int  aesni_set_decrypt_key(const u8 *userKey, int bits, aesni_key_schedule ks);
void aesni_encrypt       (const u8 *in, u8 *out, const aesni_key_schedule ks);
void aesni_decrypt       (const u8 *in, u8 *out, const aesni_key_schedule ks);

#endif /* AESNI_H */
