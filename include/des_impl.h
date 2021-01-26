#if !defined(DES_IMPL_H)
#define DES_IMPL_H

#include <stdint.h>

typedef uint64_t (*procFunc)(uint64_t key, uint64_t blk);

uint64_t padLastBlk(uint64_t lastBlk, int size);
int getPadLen(uint64_t lastBlk);

uint64_t procBlk(uint64_t key, uint64_t blk, procFunc func);

uint64_t itersEncrypt(uint64_t key, uint64_t blk);
uint64_t itersDecrypt(uint64_t key, uint64_t blk);

#endif  // DES_IMPL_H
