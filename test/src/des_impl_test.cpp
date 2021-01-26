#include <gtest/gtest.h>

extern "C" {
#include "des_impl.h"
}

TEST(padLastBlkTest, demoTest) {
    EXPECT_EQ(padLastBlk(0, 0), 0x0808080808080808);
    EXPECT_EQ(padLastBlk(0x12, 1), 0x0707070707070712);
    EXPECT_EQ(padLastBlk(0x0123456789ABCD, 7), 0x010123456789ABCD);
}

TEST(getPadLenTest, demoTest) {
    EXPECT_EQ(getPadLen(0x0808080808080808), 8);
    EXPECT_EQ(getPadLen(0x0707070707070712), 7);
    EXPECT_EQ(getPadLen(0x010123456789ABCD), 1);
}
