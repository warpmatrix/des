#include <stdio.h>
#include <string.h>

#include "des.h"

int main(int argc, char const *argv[]) {
    char key[] = "12345678";
    char message[] = "1234567";
    // char [] message contains a null terminator '\0'    
    int msgLen = strlen(message) + 1;

    int ciphLen = calCiphLen(msgLen);
    uint64_t ciphTxt[ciphLen];
    encrypt(key, message, msgLen, ciphTxt);
    printf("after encryption:\n");
    for (int i = 0; i < ciphLen; i++) {
        printf("%lX ", ciphTxt[i]);
    }
    printf("\n");

    char decryMsg[ciphLen];
    int decryLen = decrypt(key, ciphTxt, ciphLen, decryMsg);
    printf("after decryption:\n");
    printf("%s\n", decryMsg);
    return 0;
}
