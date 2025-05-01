#ifndef AESNI_H
#define AESNI_H

#include <stdint.h>

/* keySchedule needs room for 15 round-keys of 16 bytes each = 240 bytes */
typedef uint8_t aesni_key_schedule[240];

/* defined in your .S file: */
int  aesni_set_encrypt_key(const uint8_t *userKey, int bits, aesni_key_schedule ks);
int  aesni_set_decrypt_key(const uint8_t *userKey, int bits, aesni_key_schedule ks);
void aesni_encrypt       (const uint8_t *in, uint8_t *out, const aesni_key_schedule ks);
void aesni_decrypt       (const uint8_t *in, uint8_t *out, const aesni_key_schedule ks);

#endif /* AESNI_H */
