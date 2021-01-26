#include "des_impl.h"

#include <memory.h>

#include "feistel.h"
#include "table.h"
#include "utils.h"

uint64_t padLastBlk(uint64_t lastBlk, int size) {
    uint64_t ret;
    memcpy(&ret, &lastBlk, size);
    int padLen = sizeof(ret) - size;
    memset((uint8_t *)&ret + size, padLen, padLen);
    return ret;
}
int getPadLen(uint64_t lastBlk) {
    uint8_t *ptr = (uint8_t *)&lastBlk;
    return ptr[sizeof(lastBlk) - 1];
}

uint64_t procBlk(uint64_t key, uint64_t blk, procFunc func) {
    uint64_t tmp;
    permute((void *)&blk, (void *)&tmp, sizeof(blk), IP, sizeof(IP) / sizeof(*IP));
    uint64_t ret = func(key, tmp);
    swap((uint32_t *)&ret, (uint32_t *)&ret + 1, sizeof(uint32_t));
    permute((void *)&ret, (void *)&ret, sizeof(ret), IP_INV,
            sizeof(IP_INV) / sizeof(*IP_INV));
    return ret;
}

uint64_t itersEncrypt(uint64_t key, uint64_t blk) {
    uint48_t subKeys[16];
    genSubKeys(key, subKeys);
    for (int i = 0; i < 16; i++) {
        uint32_t *lPtr = (uint32_t *)&blk;
        uint32_t *rPtr = (uint32_t *)&blk + 1;
        uint32_t feiRes = feistel(*rPtr, subKeys[i]);
        *lPtr ^= feiRes;
        swap(lPtr, rPtr, sizeof(uint32_t));
    }
    return blk;
}

uint64_t itersDecrypt(uint64_t key, uint64_t blk) {
    uint48_t subKeys[16];
    genSubKeys(key, subKeys);
    for (int i = 15; i >= 0; i--) {
        uint32_t *lPtr = (uint32_t *)&blk;
        uint32_t *rPtr = (uint32_t *)&blk + 1;
        uint32_t feiRes = feistel(*rPtr, subKeys[i]);
        *lPtr ^= feiRes;
        swap(lPtr, rPtr, sizeof(uint32_t));
    }
    return blk;
}
