#include <gtest/gtest.h>
#include <stdint.h>

extern "C" {
#include "utils.h"
#include "table.h"
}

TEST(permuteTest, diffDestTest) {
    uint64_t src = 0x1234567890ABCDEF;
    uint64_t dest;
    permute(&src, &dest, sizeof(src), IP, sizeof(IP) / sizeof(*IP));
    for (int i = 0; i < sizeof(IP) / sizeof(*IP); i++) {
        int destVal = getBit(&dest, i);
        int srcVal = getBit(&src, IP[i] - 1);
        if (srcVal != destVal) {
            printf("idx: %d\n", i);
        }
        EXPECT_EQ(srcVal, destVal);
    }
}
TEST(permuteTest, sameDestTest) {
    uint64_t data = 0x1234567890ABCDEF;
    uint64_t copy = data;
    permute(&data, &data, sizeof(data), IP, sizeof(IP) / sizeof(*IP));
    for (int i = 0; i < sizeof(IP) / sizeof(*IP); i++) {
        int destVal = getBit(&data, i);
        int srcVal = getBit(&copy, IP[i] - 1);
        if (srcVal != destVal) {
            printf("idx: %d\n", i);
        }
        EXPECT_EQ(srcVal, destVal);
    }
}
TEST(permuteTest, rExtTest) {
    uint32_t rBlk = 0x12345678;
    uint64_t rExt;
    permute(&rBlk, &rExt, sizeof(rBlk), E_EXT, sizeof(E_EXT) / sizeof(*E_EXT));
    for (int i = 0; i < sizeof(E_EXT) / sizeof(*E_EXT); i++) {
        int destVal = getBit(&rExt, i);
        int srcVal = getBit(&rBlk, E_EXT[i] - 1);
        if (srcVal != destVal) {
            printf("idx: %d\n", i);
        }
        EXPECT_EQ(srcVal, destVal);
    }
}

TEST(bitOperTest, getBitTest) {
    int data = 0b1010010001;
    for (int i = 0; i < sizeof(data) << 3; i++) {
        int bitVal = getBit(&data, i);
        if (i == 0 || i == 4 || i == 7 || i == 9) {
            EXPECT_EQ(bitVal, 1);
        } else {
            EXPECT_EQ(bitVal, 0);
        }
    }
}
TEST(bitOperTest, setBitTest) {
    int data = 0b1010010001;
    int dest = 0;
    for (int i = 0; i < sizeof(data) << 3; i++) {
        int srcVal = getBit(&data, i);
        setBit(&dest, i, srcVal);
        int destVal = getBit(&dest, i);
        EXPECT_EQ(srcVal, destVal);
    }
}

TEST(swapTest, swapIntTest) {
    int num1 = 123;
    int num2 = 456;
    swap(&num1, &num2, sizeof(num1));
    EXPECT_EQ(num2, 123);
    EXPECT_EQ(num1, 456);
}
