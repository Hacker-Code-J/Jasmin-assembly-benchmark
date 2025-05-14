// gcc -c -O3 -march=x86-64 sha3_256_ref.S -o sha3_256_ref.o
// gcc -c -O3 jasmin_sha3_256_ref.c -o jasmin_sha3_256_ref.o
// gcc jasmin_sha3_256_ref.o sha3_256_ref.o -o jasmin_sha3_256_ref

#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>

#include "sha3_256_ref.h"

static void print_info(const char *algname, const char *arch, const char *impl)
{
  printf("// {\"%s\" : { architecture : \"%s\", implementation : \"%s\" form \"%s\"} }",
         algname, arch, impl, "Jasmin");
  printf("\n");
}

static void print_u8(const uint8_t *a, size_t l)
{
  size_t i;

  if(l == 0)
  { return; }

  printf("{\n  ");
  for(i=0; i<(l-1); i++)
  { printf("0x%02" PRIx8 ", ", a[i]);
    if((i+1)%16 == 0)
    { printf("\n  "); }
  }

  printf("0x%02" PRIx8 "\n};\n", a[i]);
  return;
}

static void print_str_u8(const char *str, const uint8_t *a, size_t l)
{
  if( l == 0 )
  { printf("uint8_t *%s = NULL;\n", str);
    return;
  }

  printf("uint8_t %s[%zu] = ",str, l);
  print_u8(a, l);
}

int main(void)
{
  int r;
  uint8_t hash[JADE_HASH_sha3_256_amd64_ref_BYTES];
  uint8_t input[] = {0x61, 0x62, 0x63};

  //
  r = jade_hash_sha3_256_amd64_ref(hash, input, sizeof(input));
    assert(r == 0);

  print_info(JADE_HASH_sha3_256_amd64_ref_ALGNAME, JADE_HASH_sha3_256_amd64_ref_ARCH, JADE_HASH_sha3_256_amd64_ref_IMPL);
  print_str_u8("input", input, sizeof(input));
  print_str_u8("hash", hash, JADE_HASH_sha3_256_amd64_ref_BYTES);

  return 0;
}

