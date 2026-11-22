#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 // 64 bits / 8 bytes

// Bit padding: 1 bit followed by 0 bits (0x80 then 0x00)
int padBitMethod(const uint8_t *in, int len, uint8_t *out) {
    memcpy(out, in, len);
    // Number of padding bytes:
    // If len % BLOCK_SIZE == 0, an entire new padding block is added!
    int padBytes = BLOCK_SIZE - (len % BLOCK_SIZE);
    out[len] = 0x80;
    for (int i = 1; i < padBytes; i++) {
        out[len + i] = 0x00;
    }
    return len + padBytes;
}

int unpadBitMethod(const uint8_t *in, int paddedLen, uint8_t *out) {
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
    return -1;
}

void printBlocks(const uint8_t *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
        if ((i + 1) % BLOCK_SIZE == 0) printf("| ");
    }
    printf("\n");
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 34: BLOCK CIPHER MODES PADDING ANALYSIS \n");
    printf("               (ECB, CBC, and CFB Modes)              \n");
    printf("======================================================\n\n");

    printf("Analysis for ECB, CBC, and CFB Modes:\n");
    printf("1. ECB & CBC require the input to be an exact multiple of the block size.\n");
    printf("2. CFB mode requires plaintext to be a multiple of the segment size.\n");
    printf("3. Bit Padding Method: A single 1-bit followed by as few zero bits as necessary.\n\n");

    printf("Core Question:\n");
    printf("\"What is the motivation for including a padding block when padding is not needed?\"\n\n");
    printf("Answer:\n");
    printf("- Without an extra block, if a valid plaintext message happens to end with\n");
    printf("  a byte with its high bit set followed by 0x00 bytes, the receiver cannot know\n");
    printf("  whether these bytes were part of the user's data or were added as padding!\n");
    printf("- By mandating that EVERY message is padded, even complete blocks receive an\n");
    printf("  extra padding block. The unpadding routine can therefore strip padding\n");
    printf("  UNCONDITIONALLY and UNAMBIGUOUSLY without any risk of data truncation!\n\n");

    // Demonstration 1: Partial block
    uint8_t data1[32] = "Network"; // 7 bytes
    uint8_t padded1[32], unpadded1[32];
    int p1 = padBitMethod(data1, 7, padded1);

    printf("Test 1: Message length 7 bytes (Partial Block):\n");
    printf("  Padded (%d bytes): ", p1);
    printBlocks(padded1, p1);
    unpadBitMethod(padded1, p1, unpadded1);
    printf("  Recovered: \"%s\"\n\n", unpadded1);

    // Demonstration 2: Full block
    uint8_t data2[32] = "Security"; // 8 bytes (Exact multiple of 8)
    uint8_t padded2[32], unpadded2[32];
    int p2 = padBitMethod(data2, 8, padded2);

    printf("Test 2: Message length 8 bytes (Full Block, Extra Block Appended):\n");
    printf("  Padded (%d bytes): ", p2);
    printBlocks(padded2, p2);
    unpadBitMethod(padded2, p2, unpadded2);
    printf("  Recovered: \"%s\" (Unambiguous removal!)\n", unpadded2);

    return 0;
}
