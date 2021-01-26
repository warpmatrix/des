#include <gtest/gtest.h>

extern "C" {
#include "des.h"
}

TEST(calCiphLenTest, demoTest) {
    EXPECT_EQ(calCiphLen(0), 1);
    EXPECT_EQ(calCiphLen(1), 1);
    EXPECT_EQ(calCiphLen(2), 1);
    EXPECT_EQ(calCiphLen(7), 1);
    EXPECT_EQ(calCiphLen(8), 2);
    EXPECT_EQ(calCiphLen(9), 2);
    EXPECT_EQ(calCiphLen(15), 2);
    EXPECT_EQ(calCiphLen(16), 3);
}

TEST(decryptTest, innerPaddingTest) {
    char key[] = "12345678";
    char message[] = "1234567";
    int msgLen = strlen(message);

    int ciphLen = calCiphLen(msgLen);
    uint64_t ciphTxt[ciphLen];
    encrypt(key, message, msgLen, ciphTxt);

    char decryMsg[ciphLen];
    int decryLen = decrypt(key, ciphTxt, ciphLen, decryMsg);

    EXPECT_EQ(msgLen, decryLen);
    EXPECT_EQ(memcmp(message, decryMsg, msgLen), 0);
}
TEST(decryptTest, outerPaddingTest) {
    char key[] = "12345678";
    char message[] = "12345678";
    int msgLen = strlen(message);

    int ciphLen = calCiphLen(msgLen);
    uint64_t ciphTxt[ciphLen];
    encrypt(key, message, msgLen, ciphTxt);

    char decryMsg[ciphLen];
    int decryLen = decrypt(key, ciphTxt, ciphLen, decryMsg);

    EXPECT_EQ(msgLen, decryLen);
    EXPECT_EQ(memcmp(message, decryMsg, msgLen), 0);
}
