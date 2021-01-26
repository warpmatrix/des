#include <gtest/gtest.h>

extern "C" {
#include "feistel.h"
#include "utils.h"
}

TEST(rotLeftShiftTest, demoTest) {
    uint56_t data = 0x1234567890ABCD;
    int offset = 1;
    uint56_t res = rotLeftShift(data, offset);
    int len = 28;
    for (int i = 0; i < len; i++) {
        EXPECT_EQ(getBit(&data, i), getBit(&res, (i + offset) % len));
        EXPECT_EQ(getBit(&data, len + i), getBit(&res, len + (i + offset) % len));
    }
    offset = 2;
    res = rotLeftShift(data, offset);
    for (int i = 0; i < len; i++) {
        EXPECT_EQ(getBit(&data, i), getBit(&res, (i + offset) % len));
        EXPECT_EQ(getBit(&data, len + i), getBit(&res, len + (i + offset) % len));
    }
}
