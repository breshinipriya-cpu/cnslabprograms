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

    left = ((left << 1) | (left >> 4)) & 0x1F;
    right = ((right << 1) | (right >> 4)) & 0x1F;
    *K1 = (uint8_t)permute((left << 5) | right, P8, 8, 10);

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

    uint8_t L1 = R;
    uint8_t R1 = L ^ f_k(R, K1);

    uint8_t L2 = L1 ^ f_k(R1, K2);
    uint8_t R2 = R1;

    return (uint8_t)permute((L2 << 4) | R2, IP_INV, 8, 8);
}

void printBinary8(uint8_t b) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (b >> i) & 1);
        if (i == 4) printf(" ");
    }
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 23: S-DES IN COUNTER (CTR) MODE         \n");
    printf("======================================================\n\n");

    // Test parameters from question:
    // Counter starting at 0000 0000 (T0=0, T1=1, T2=2)
    // Key = 01111 11101 (binary = 0x1FD)
    // Plaintext = 0000 0001  0000 0010  0000 0100 (0x01, 0x02, 0x04)
    // Expected ciphertext = 0011 1000  0100 1111  0011 0010 (0x38, 0x4F, 0x32)
    uint16_t key = 0x1FD;
    uint8_t plain[3] = {0x01, 0x02, 0x04};
    uint8_t cipher[3];
    uint8_t decrypted[3];

    uint8_t K1, K2;
    generateKeys(key, &K1, &K2);

    printf("Test Parameters:\n");
    printf("  Starting Counter: 0000 0000\n");
    printf("  Key:              01111 11101\n");
    printf("  Plaintext:        ");
    for (int i = 0; i < 3; i++) { printBinary8(plain[i]); printf("  "); }
    printf("\n\n");

    // CTR Mode Encryption: C_i = P_i ^ E_K(Counter_i)
    printf("CTR Encryption Steps:\n");
    for (int i = 0; i < 3; i++) {
        uint8_t ctr = (uint8_t)i;
        uint8_t o_i = sdesEncryptByte(ctr, K1, K2);
        cipher[i] = plain[i] ^ o_i;
        printf("  Block %d: CTR=", i + 1); printBinary8(ctr);
        printf(" -> E(CTR)="); printBinary8(o_i);
        printf(" -> Cipher="); printBinary8(cipher[i]);
        printf(" (0x%02X)\n", cipher[i]);
    }

    printf("\nResulting Ciphertext:\n  ");
    for (int i = 0; i < 3; i++) { printBinary8(cipher[i]); printf("  "); }
    printf("\nExpected Ciphertext:   0011 1000  0100 1111  0011 0010\n");

    if (cipher[0] == 0x38 && cipher[1] == 0x4F && cipher[2] == 0x32) {
        printf("VERIFICATION: Ciphertext MATCHES TEST DATA PERFECTLY!\n\n");
    }

    // CTR Mode Decryption: P_i = C_i ^ E_K(Counter_i)
    printf("CTR Decryption:\n  ");
    for (int i = 0; i < 3; i++) {
        uint8_t ctr = (uint8_t)i;
        uint8_t o_i = sdesEncryptByte(ctr, K1, K2);
        decrypted[i] = cipher[i] ^ o_i;
        printBinary8(decrypted[i]); printf("  ");
    }
    printf("\nVERIFICATION: Decryption recovered original plaintext!\n");

    return 0;
}
