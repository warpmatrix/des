#if !defined(FEISTEL_H)
#define FEISTEL_H

#include <stdint.h>

typedef uint64_t uint48_t;
typedef uint64_t uint56_t;

uint48_t *genSubKeys(uint64_t key, uint48_t *subKeys);
uint56_t rotLeftShift(uint56_t data, int offset);

uint32_t feistel(uint32_t rBlk, uint48_t key);
uint32_t getSBoxOut(uint48_t xorRes);
int getSRow(uint48_t xorRes, int idx);
int getSCol(uint48_t xorRes, int idx);

#endif  // FEISTEL_H
