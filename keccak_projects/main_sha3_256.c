#include <stdint.h>
#include "KeccakP-1600-SnP.h"

int sha3(uint8_t *hash, const uint8_t *input, uint64_t input_length) {
    KeccakP1600_plain8_state state;
    unsigned int offset = 0;

    // Initialize Keccak state
    KeccakP1600_Initialize(&state);

    // Absorb the input bytes
    for (unsigned int i = 0; i < input_length; i++) {
        KeccakP1600_AddByte(&state, input[i], offset);
        offset = (offset + 1) % 200;  // Keccak state is 200 bytes
    }

    // Padding step: Add padding byte 0x06
    KeccakP1600_AddByte(&state, 0x06, offset);
    offset = (offset + 1) % 200;  // Move to the next offset

    // Add the 0x80 byte indicating the end of the message
    KeccakP1600_AddByte(&state, 0x80, offset);
    offset = (offset + 1) % 200;

    // Apply the 24 rounds of Keccak permutation
    KeccakP1600_Permute_24rounds(&state);


    // Extract the hash (32 bytes for SHA3-256)
    KeccakP1600_ExtractBytes(&state, hash, 0, 32); // For SHA3-256, we extract 32 bytes

    return 0; // Successful execution
}