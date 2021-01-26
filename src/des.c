#include "des.h"

#include <memory.h>

#include "des_impl.h"

inline int calCiphLen(size_t len) {
    // len / 8 + 1
    int ret = (len >> 3) + 1;
    return ret;
}

uint64_t *encrypt(const void *key, const void *msg, size_t msgSize, uint64_t *ciphTxt) {
    const uint64_t *msgPtr = msg;
    int ciphLen = calCiphLen(msgSize);
    for (int i = 0; i < ciphLen - 1; i++) {
        ciphTxt[i] = procBlk(*(uint64_t *)key, msgPtr[i], itersEncrypt);
    }
    uint64_t lastBlk = padLastBlk(msgPtr[ciphLen - 1], msgSize & 7);
    ciphTxt[ciphLen - 1] = procBlk(*(uint64_t *)key, lastBlk, itersEncrypt);
    return ciphTxt;
}

int decrypt(const void *key, const uint64_t *ciphTxt, int ciphLen, void *msg) {
    uint64_t *msgPtr = msg;
    for (int i = 0; i < ciphLen - 1; i++) {
        msgPtr[i] = procBlk(*(uint64_t *)key, ciphTxt[i], itersDecrypt);
    }
    uint64_t lastBlk = procBlk(*(uint64_t *)key, ciphTxt[ciphLen - 1], itersDecrypt);
    int padLen = getPadLen(lastBlk);
    memcpy(&msgPtr[ciphLen - 1], &lastBlk, sizeof(*msgPtr) - padLen);
    return ciphLen * sizeof(*ciphTxt) - padLen;
}
