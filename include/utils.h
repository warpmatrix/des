#if !defined(UTILS_H)
#define UTILS_H

#include <stddef.h>

void *permute(const void *src, void *dest, size_t srcSiz, const int *table, int tblLen);

int getBit(const void *data, int bitIdx);
void *setBit(void *data, int bitIdx, int bitVal);

void swap(void *lhs, void *rhs, size_t size);

#endif  // UTILS_H
