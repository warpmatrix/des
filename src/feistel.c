#include "feistel.h"

#include "table.h"
#include "utils.h"

uint48_t *genSubKeys(uint64_t key, uint48_t *subKeys) {
    uint56_t tmpKey;
    permute((void *)&key, (void *)&tmpKey, sizeof(key), PC1, sizeof(PC1) / sizeof(*PC1));
    for (int i = 0; i < 16; i++) {
        int loopIdx = i + 1;
        int offset = 2;
        if (loopIdx == 1 || loopIdx == 2 || loopIdx == 9 || loopIdx == 16) offset = 1;
        tmpKey = rotLeftShift(tmpKey, offset);
        permute((void *)&tmpKey, (void *)&subKeys[i], sizeof(tmpKey), PC2,
                sizeof(PC2) / sizeof(*PC2));
    }
    return subKeys;
}

uint56_t rotLeftShift(uint56_t data, int offset) {
    int tmp1[offset], tmp2[offset];
    const int len = 28;
    const int base = len - offset;
    for (int i = 0; i < offset; i++) {
        tmp1[i] = getBit(&data, base + i);
        tmp2[i] = getBit(&data, len + base + i);
    }
    for (int i = len - offset - 1; i >= 0; i--) {
        int bitVal = getBit(&data, i);
        setBit(&data, i + offset, bitVal);
        bitVal = getBit(&data, len + i);
        setBit(&data, len + i + offset, bitVal);
    }
    for (int i = 0; i < offset; i++) {
        setBit(&data, i, tmp1[i]);
        setBit(&data, len + i, tmp2[i]);
    }
    return data;
}

uint32_t feistel(uint32_t rBlk, uint48_t key) {
    uint48_t rExt;
    permute((void *)&rBlk, (void *)&rExt, sizeof(rBlk), E_EXT,
            sizeof(E_EXT) / sizeof(*E_EXT));
    uint32_t sBoxOut = getSBoxOut(rExt ^ key);
    uint32_t feiRes;
    permute((void *)&sBoxOut, (void *)&feiRes, sizeof(sBoxOut), P_PERM,
            sizeof(P_PERM) / sizeof(*P_PERM));
    return feiRes;
}

uint32_t getSBoxOut(uint48_t xorRes) {
    uint32_t ret;
    for (int i = 0; i < 8; i++) {
        uint8_t *ptr = (uint8_t *)&ret + (i >> 1);
        int row = getSRow(xorRes, i);
        int col = getSCol(xorRes, i);
        if (i % 2 == 0) {
            *ptr = S_BOXS[i][row][col];
        } else {
            *ptr |= S_BOXS[i][row][col] << 4;
        }
    }
    return ret;
}

inline int getSRow(uint48_t xorRes, int idx) {
    return (getBit(&xorRes, idx * 6) << 1) | getBit(&xorRes, idx * 6 + 5);
}

inline int getSCol(uint48_t xorRes, int idx) {
    int ret = 0;
    for (int i = 1; i <= 4; i++) {
        ret = (ret << 1) | getBit(&xorRes, idx * 6 + i);
    }
    return ret;
}
