// SPDX-License-Identifier: Apache-2.0 OR CC0-1.0

#if defined(__unix__) || defined(__APPLE__)
// #include <oqs/rand.h>
#include "libjade_randombytes.h"
#include <stdlib.h>
#include <time.h>

void __jasmin_syscall_randombytes__(uint8_t *_x, uint64_t xlen) {
	srand(time(NULL));
	for (uint64_t i = 0; i < xlen; i++) {
		_x[i] = rand() % 256;
	}
	// OQS_randombytes(_x, xlen);
}
#endif
