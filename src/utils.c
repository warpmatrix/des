#include "utils.h"

#include <memory.h>
#include <stdint.h>

typedef uint64_t uint48_t;
typedef uint64_t uint56_t;

void *permute(const void *src, void *dest, size_t srcSiz, const int *table, int tblLen) {
    uint8_t srcCopy[srcSiz];
    memcpy(srcCopy, src, srcSiz);
    for (int i = 0; i < tblLen; i++) {
        int bitVal = getBit(srcCopy, table[i] - 1);
        setBit(dest, i, bitVal);
    }
    return dest;
}

inline int getBit(const void *data, int bitIdx) {
    const uint8_t *ptr = data;
    // (ptr[bitIdx / 8] >> (bitIdx % 8)) % 2
    int bitVal = (ptr[bitIdx >> 3] >> (bitIdx & 7)) & 1;
    return bitVal;
}

inline void *setBit(void *data, int bitIdx, int bitVal) {
    uint8_t *ptr = data;
    int byteIdx = bitIdx >> 3;
    ptr[byteIdx] = bitVal ? ptr[byteIdx] | (1 << (bitIdx & 7)) 
                          : ptr[byteIdx] & ~(1 << (bitIdx & 7));
    return data;
}

inline void swap(void *lhs, void *rhs, size_t size) {
    uint8_t tmp[size];
    memcpy(tmp, lhs, size);
    memcpy(lhs, rhs, size);
    memcpy(rhs, tmp, size);
}
