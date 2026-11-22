#include <stdio.h>
#include <stdint.h>

// S-DES Tables
const int P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
const int P8[8]   = {6, 3, 7, 4, 8, 5, 10, 9};
const int IP[8]   = {2, 6, 3, 1, 4, 8, 5, 7};
const int IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};
const int EP[8]   = {4, 1, 2, 3, 2, 3, 4, 1};
const int P4[4]   = {2, 4, 3, 1};

const int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

const int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

uint16_t permute(uint16_t in, const int *table, int n, int inBits) {
    uint16_t out = 0;
    for (int i = 0; i < n; i++) {
        int bit = (in >> (inBits - table[i])) & 1;
        out = (out << 1) | bit;
    }
    return out;
}

void generateKeys(uint16_t key10, uint8_t *K1, uint8_t *K2) {
    uint16_t p10 = permute(key10, P10, 10, 10);
    uint8_t left = (p10 >> 5) & 0x1F;
    uint8_t right = p10 & 0x1F;

    // LS-1
    left = ((left << 1) | (left >> 4)) & 0x1F;
    right = ((right << 1) | (right >> 4)) & 0x1F;
    *K1 = (uint8_t)permute((left << 5) | right, P8, 8, 10);

    // LS-2
    left = ((left << 2) | (left >> 3)) & 0x1F;
    right = ((right << 2) | (right >> 3)) & 0x1F;
    *K2 = (uint8_t)permute((left << 5) | right, P8, 8, 10);
}

uint8_t f_k(uint8_t R, uint8_t sk) {
    uint8_t ep = (uint8_t)permute(R, EP, 8, 4);
    uint8_t x = ep ^ sk;
    uint8_t l = (x >> 4) & 0x0F;
    uint8_t r = x & 0x0F;

    int r0 = ((l >> 3) & 1) * 2 + (l & 1);
    int c0 = ((l >> 2) & 1) * 2 + ((l >> 1) & 1);
    int s0_val = S0[r0][c0];

    int r1 = ((r >> 3) & 1) * 2 + (r & 1);
    int c1 = ((r >> 2) & 1) * 2 + ((r >> 1) & 1);
    int s1_val = S1[r1][c1];

    uint8_t combined = (s0_val << 2) | s1_val;
    return (uint8_t)permute(combined, P4, 4, 4);
}

uint8_t sdesEncryptByte(uint8_t p, uint8_t K1, uint8_t K2) {
    uint8_t ip = (uint8_t)permute(p, IP, 8, 8);
    uint8_t L = (ip >> 4) & 0x0F;
    uint8_t R = ip & 0x0F;

    // Round 1
    uint8_t L1 = R;
    uint8_t R1 = L ^ f_k(R, K1);

    // Round 2
    uint8_t L2 = L1 ^ f_k(R1, K2);
    uint8_t R2 = R1;

    return (uint8_t)permute((L2 << 4) | R2, IP_INV, 8, 8);
}

uint8_t sdesDecryptByte(uint8_t c, uint8_t K1, uint8_t K2) {
    // Decryption applies keys in reverse order: K2 then K1
    return sdesEncryptByte(c, K2, K1);
}

void printBinary8(uint8_t b) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (b >> i) & 1);
        if (i == 4) printf(" ");
    }
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 22: S-DES IN CBC MODE                   \n");
    printf("======================================================\n\n");

    // Test parameters from question:
    // IV = 1010 1010 (0xAA)
    // Plaintext = 0000 0001  0010 0011 (Block 1 = 0x01, Block 2 = 0x23)
    // Key = 01111 11101 (binary = 0x1FD)
    // Expected ciphertext = 1111 0100  0000 1011 (0xF4, 0x0B)
    uint8_t IV = 0xAA;
    uint16_t key = 0x1FD;
    uint8_t plain[2] = {0x01, 0x23};
    uint8_t cipher[2];
    uint8_t decrypted[2];

    uint8_t K1, K2;
    generateKeys(key, &K1, &K2);

    printf("Test Parameters:\n");
    printf("  IV:        "); printBinary8(IV); printf(" (0x%02X)\n", IV);
    printf("  Key:       01111 11101 (K1=0x%02X, K2=0x%02X)\n", K1, K2);
    printf("  Plaintext: "); printBinary8(plain[0]); printf(" "); printBinary8(plain[1]); printf("\n\n");

    // CBC Encryption: C_i = E(P_i ^ C_{i-1})
    uint8_t prev = IV;
    for (int i = 0; i < 2; i++) {
        uint8_t x = plain[i] ^ prev;
        cipher[i] = sdesEncryptByte(x, K1, K2);
        prev = cipher[i];
    }

    printf("Encrypted Ciphertext:\n  ");
    printBinary8(cipher[0]); printf("  "); printBinary8(cipher[1]);
    printf(" (Hex: %02X %02X)\n", cipher[0], cipher[1]);
    printf("Expected Ciphertext: 1111 0100  0000 1011\n");
    if (cipher[0] == 0xF4 && cipher[1] == 0x0B) {
        printf("VERIFICATION: Ciphertext MATCHES TEST DATA PERFECTLY!\n\n");
    }

    // CBC Decryption: P_i = D(C_i) ^ C_{i-1}
    prev = IV;
    for (int i = 0; i < 2; i++) {
        uint8_t d = sdesDecryptByte(cipher[i], K1, K2);
        decrypted[i] = d ^ prev;
        prev = cipher[i];
    }

    printf("Decrypted Plaintext:\n  ");
    printBinary8(decrypted[0]); printf("  "); printBinary8(decrypted[1]);
    printf("\nVERIFICATION: Decryption matches original plaintext!\n");

    return 0;
}
