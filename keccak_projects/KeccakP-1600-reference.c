/*
The eXtended Keccak Code Package (XKCP)
https://github.com/XKCP/XKCP

The Keccak-p permutations, designed by Guido Bertoni, Joan Daemen, Michaël Peeters and Gilles Van Assche.

Implementation by the designers, hereby denoted as "the implementer".

For more information, feedback or questions, please refer to the Keccak Team website:
https://keccak.team/

To the extent possible under law, the implementer has waived all copyright
and related or neighboring rights to the source code in this file.
http://creativecommons.org/publicdomain/zero/1.0/

---

This file implements Keccak-p[1600] in a SnP-compatible way.
Please refer to SnP-documentation.h for more details.

This implementation comes with KeccakP-1600-SnP.h in the same folder.
Please refer to LowLevel.build for the exact list of other files it must be combined with.
*/

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "KeccakP-1600-SnP.h"

typedef uint64_t tKeccakLane;

#define maxNrRounds 24
#define nrLanes 25
#define index(x, y) (((x)%5)+5*((y)%5))

static const tKeccakLane KeccakRoundConstants[maxNrRounds] =
{
    0x0000000000000001,
    0x0000000000008082,
    0x800000000000808a,
    0x8000000080008000,
    0x000000000000808b,
    0x0000000080000001,
    0x8000000080008081,
    0x8000000000008009,
    0x000000000000008a,
    0x0000000000000088,
    0x0000000080008009,
    0x000000008000000a,
    0x000000008000808b,
    0x800000000000008b,
    0x8000000000008089,
    0x8000000000008003,
    0x8000000000008002,
    0x8000000000000080,
    0x000000000000800a,
    0x800000008000000a,
    0x8000000080008081,
    0x8000000000008080,
    0x0000000080000001,
    0x8000000080008008,
};

static const unsigned int KeccakRhoOffsets[nrLanes] =
{
     0,  1, 62, 28, 27, 36, 44,  6, 55, 20,  3, 10, 43, 25, 39, 41, 45, 15, 21,  8, 18,  2, 61, 56, 14
};

/* ---------------------------------------------------------------- */

void KeccakP1600_Initialize(KeccakP1600_plain8_state *state)
{
    memset(state->A, 0, sizeof(state->A));
}

/* ---------------------------------------------------------------- */

void KeccakP1600_AddByte(KeccakP1600_plain8_state *state, unsigned char byte, unsigned int offset)
{
    assert(offset < 200);
    state->A[offset] ^= byte;
}

/* ---------------------------------------------------------------- */

void KeccakP1600_AddBytes(KeccakP1600_plain8_state *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    unsigned int i;

    assert(offset < 200);
    assert(offset+length <= 200);
    for(i=0; i<length; i++)
        state->A[offset+i] ^= data[i];
}

/* ---------------------------------------------------------------- */

void KeccakP1600_OverwriteBytes(KeccakP1600_plain8_state *state, const unsigned char *data, unsigned int offset, unsigned int length)
{
    assert(offset < 200);
    assert(offset+length <= 200);
    memcpy(state->A+offset, data, length);
}

/* ---------------------------------------------------------------- */

void KeccakP1600_OverwriteWithZeroes(KeccakP1600_plain8_state *state, unsigned int byteCount)
{
    assert(byteCount <= 200);
    memset(state->A, 0, byteCount);
}

/* ---------------------------------------------------------------- */

void KeccakP1600OnWords(tKeccakLane *state, unsigned int nrRounds);
void KeccakP1600Round(tKeccakLane *state, unsigned int indexRound);
static void theta(tKeccakLane *A);
static void rho(tKeccakLane *A);
static void pi(tKeccakLane *A);
static void chi(tKeccakLane *A);
static void iota(tKeccakLane *A, unsigned int indexRound);

void KeccakP1600_Permute_Nrounds(KeccakP1600_plain8_state *state, unsigned int nrounds)
{
    KeccakP1600OnWords((tKeccakLane*)state->A, nrounds);
}

void KeccakP1600_Permute_12rounds(KeccakP1600_plain8_state *state)
{
    KeccakP1600_Permute_Nrounds(state, 12);
}

void KeccakP1600_Permute_24rounds(KeccakP1600_plain8_state *state)
{
    KeccakP1600_Permute_Nrounds(state, 24);
}

void KeccakP1600OnWords(tKeccakLane *state, unsigned int nrRounds)
{
    unsigned int i;

    for(i=(maxNrRounds-nrRounds); i<maxNrRounds; i++)
        KeccakP1600Round(state, i);
}

void KeccakP1600Round(tKeccakLane *state, unsigned int indexRound)
{
    theta(state);
    rho(state);
    pi(state);
    chi(state);
    iota(state, indexRound);
}

#define ROL64(a, offset) ((offset != 0) ? ((((tKeccakLane)a) << offset) ^ (((tKeccakLane)a) >> (64-offset))) : a)

static void theta(tKeccakLane *A)
{
    unsigned int x, y;
    tKeccakLane C[5], D[5];

    for(x=0; x<5; x++) {
        C[x] = 0;
        for(y=0; y<5; y++)
            C[x] ^= A[index(x, y)];
    }
    for(x=0; x<5; x++)
        D[x] = ROL64(C[(x+1)%5], 1) ^ C[(x+4)%5];
    for(x=0; x<5; x++)
        for(y=0; y<5; y++)
            A[index(x, y)] ^= D[x];
}

static void rho(tKeccakLane *A)
{
    unsigned int x, y;

    for(x=0; x<5; x++) for(y=0; y<5; y++)
        A[index(x, y)] = ROL64(A[index(x, y)], KeccakRhoOffsets[index(x, y)]);
}

static void pi(tKeccakLane *A)
{
    unsigned int x, y;
    tKeccakLane tempA[25];

    for(x=0; x<5; x++) for(y=0; y<5; y++)
        tempA[index(x, y)] = A[index(x, y)];
    for(x=0; x<5; x++) for(y=0; y<5; y++)
        A[index(0*x+1*y, 2*x+3*y)] = tempA[index(x, y)];
}

static void chi(tKeccakLane *A)
{
    unsigned int x, y;
    tKeccakLane C[5];

    for(y=0; y<5; y++) {
        for(x=0; x<5; x++)
            C[x] = A[index(x, y)] ^ ((~A[index(x+1, y)]) & A[index(x+2, y)]);
        for(x=0; x<5; x++)
            A[index(x, y)] = C[x];
    }
}

static void iota(tKeccakLane *A, unsigned int indexRound)
{
    A[index(0, 0)] ^= KeccakRoundConstants[indexRound];
}

/* ---------------------------------------------------------------- */

void KeccakP1600_ExtractBytes(const KeccakP1600_plain8_state *state, unsigned char *data, unsigned int offset, unsigned int length)
{
    assert(offset < 200);
    assert(offset+length <= 200);
    memcpy(data, state->A+offset, length);
}

/* ---------------------------------------------------------------- */

void KeccakP1600_ExtractAndAddBytes(const KeccakP1600_plain8_state *state, const unsigned char *input, unsigned char *output, unsigned int offset, unsigned int length)
{
    unsigned int i;

    assert(offset < 200);
    assert(offset+length <= 200);

    for(i=0; i<length; i++)
        output[i] = input[i] ^ state->A[offset+i];
}

/* ---------------------------------------------------------------- */

void KeccakP1600_DisplayRoundConstants(FILE *f)
{
    unsigned int i;

    for(i=0; i<maxNrRounds; i++) {
        fprintf(f, "RC[%02i][0][0] = ", i);
        fprintf(f, "%08X", (unsigned int)(KeccakRoundConstants[i] >> 32));
        fprintf(f, "%08X", (unsigned int)(KeccakRoundConstants[i] & 0xFFFFFFFFULL));
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}

void KeccakP1600_DisplayRhoOffsets(FILE *f)
{
    unsigned int x, y;

    for(y=0; y<5; y++) for(x=0; x<5; x++) {
        fprintf(f, "RhoOffset[%i][%i] = ", x, y);
        fprintf(f, "%2i", KeccakRhoOffsets[index(x, y)]);
        fprintf(f, "\n");
    }
    fprintf(f, "\n");
}
