#if !defined(DES_H)
#define DES_H

#include <stddef.h>
#include <stdint.h>

int calCiphLen(size_t msgSize);
uint64_t *encrypt(const void *key, const void *msg, size_t msgSize, uint64_t *ciphTxt);

int decrypt(const void *key, const uint64_t *ciphTxt, int ciphLen, void *msg);

#endif  // DES_H
