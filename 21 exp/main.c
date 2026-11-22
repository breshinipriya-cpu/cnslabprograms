#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // 8 bytes (64 bits)

// Demonstrates bit padding (1 followed by 0s: 0x80 followed by 0x00s)
int padMessage(const uint8_t *in, int inLen, uint8_t *out) {
    memcpy(out, in, inLen);
    // Number of padding bytes needed:
    // If already multiple of BLOCK_SIZE, a full dummy block (BLOCK_SIZE bytes) is added!
    int padLen = BLOCK_SIZE - (inLen % BLOCK_SIZE);
    
    // First byte of padding has high bit set: 10000000b = 0x80
    out[inLen] = 0x80;
    // Remaining padding bytes are 0x00
    for (int i = 1; i < padLen; i++) {
        out[inLen + i] = 0x00;
    }
    return inLen + padLen;
}

// Unpad message
int unpadMessage(const uint8_t *in, int paddedLen, uint8_t *out) {
    int idx = paddedLen - 1;
    while (idx >= 0 && in[idx] == 0x00) {
        idx--;
    }
    if (idx >= 0 && in[idx] == 0x80) {
        int origLen = idx;
        memcpy(out, in, origLen);
        out[origLen] = '\0';
        return origLen;
    }
    return -1; // Invalid padding
}

void printHex(const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
        if ((i + 1) % BLOCK_SIZE == 0) printf("| ");
    }
    printf("\n");
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 21: BLOCK CIPHER PADDING MOTIVATION     \n");
    printf("======================================================\n\n");

    printf("MOTIVATION QUESTION:\n");
    printf("\"What is the motivation for including a padding block when padding is not needed?\"\n\n");
    printf("ANSWER:\n");
    printf("- In block ciphers, decryption is performed independently of application knowledge.\n");
    printf("- The unpadding routine must unambiguously determine where the user data ends\n");
    printf("  and where padding begins, without relying on external length metadata.\n");
    printf("- If a message that is an exact multiple of the block size were NOT padded,\n");
    printf("  and happened to end with bytes matching a padding pattern (e.g. 0x80 0x00...),\n");
    printf("  the receiver would mistakenly strip off valid user data!\n");
    printf("- By ALWAYS adding padding (even a full dummy block of 8 bytes when already aligned),\n");
    printf("  the receiver is guaranteed that every message ends with valid padding bytes\n");
    printf("  and can be stripped safely and unambiguously.\n\n");

    // Case 1: Message NOT aligned to block size (e.g. 5 bytes)
    uint8_t msg1[64] = "Hello";
    int len1 = 5;
    uint8_t padded1[64];
    uint8_t unpadded1[64];
    int pLen1 = padMessage(msg1, len1, padded1);

    printf("CASE 1: Message length = %d bytes (Non-multiple of %d)\n", len1, BLOCK_SIZE);
    printf("  Original message: \"%s\"\n", msg1);
    printf("  Padded hex (%d bytes):  ", pLen1);
    printHex(padded1, pLen1);
    int uLen1 = unpadMessage(padded1, pLen1, unpadded1);
    printf("  Unpadded text: \"%s\" (Length: %d)\n\n", unpadded1, uLen1);

    // Case 2: Message ALREADY aligned to block size (8 bytes = "Security")
    uint8_t msg2[64] = "Security";
    int len2 = 8;
    uint8_t padded2[64];
    uint8_t unpadded2[64];
    int pLen2 = padMessage(msg2, len2, padded2);

    printf("CASE 2: Message length = %d bytes (Exact multiple of %d)\n", len2, BLOCK_SIZE);
    printf("  Original message: \"%s\"\n", msg2);
    printf("  Padded hex (%d bytes):  ", pLen2);
    printHex(padded2, pLen2);
    printf("  Note: A full extra dummy block [80 00 00 00 00 00 00 00] was appended!\n");
    int uLen2 = unpadMessage(padded2, pLen2, unpadded2);
    printf("  Unpadded text: \"%s\" (Length: %d) -> Recovered exactly!\n", unpadded2, uLen2);

    return 0;
}
