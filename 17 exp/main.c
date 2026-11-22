#include <stdio.h>
#include <stdint.h>

// Standard DES shift schedules
const int encShifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// Decryption shift schedule:
// For round 1 (generating K16): 0 shift.
// Subsequent rounds (to get K15..K1): right shifts matching reversed schedule.
const int decShifts[16] = {0, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

// 28-bit circular left shift
uint32_t rotl28(uint32_t val, int shift) {
    return ((val << shift) | (val >> (28 - shift))) & 0x0FFFFFFF;
}

// 28-bit circular right shift
uint32_t rotr28(uint32_t val, int shift) {
    return ((val >> shift) | (val << (28 - shift))) & 0x0FFFFFFF;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 17: DES DECRYPTION KEY SCHEDULE         \n");
    printf("======================================================\n\n");

    printf("Analysis of DES Decryption Subkey Generation:\n");
    printf("- Decryption requires subkeys in reverse order: K16, K15, ..., K1.\n");
    printf("- In encryption, 16 round keys use left circular shifts.\n");
    printf("- Total left shift over 16 rounds = 1+1+2+2+2+2+2+2+1+2+2+2+2+2+2+1 = 28 bits.\n");
    printf("  Since 28 mod 28 = 0, C16 == C0 and D16 == D0!\n\n");

    printf("Reverse Shift Schedule for Decryption Process:\n");
    printf("------------------------------------------------------------\n");
    printf("Dec Round | Target Key | Right Shift Amount | Equivalent to\n");
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < 16; i++) {
        printf("   %2d     |    K%02d    |         %d          | Enc Round %02d\n",
               i + 1, 16 - i, decShifts[i], 16 - i);
    }
    printf("------------------------------------------------------------\n\n");

    // Demonstration with a dummy initial C0 / D0 (28 bits)
    uint32_t C0 = 0x0A5A5A5A & 0x0FFFFFFF;
    uint32_t D0 = 0x05B5B5B5 & 0x0FFFFFFF;

    // 1. Generate Encryption Subkey Registers (C1..C16)
    uint32_t C_enc[17], D_enc[17];
    C_enc[0] = C0; D_enc[0] = D0;
    for (int r = 1; r <= 16; r++) {
        C_enc[r] = rotl28(C_enc[r-1], encShifts[r-1]);
        D_enc[r] = rotl28(D_enc[r-1], encShifts[r-1]);
    }

    // 2. Generate Decryption Subkey Registers using Right Shifts
    uint32_t C_dec[17], D_dec[17];
    // Start directly from (C16, D16) = (C0, D0)
    uint32_t currC = C_enc[16];
    uint32_t currD = D_enc[16];

    printf("Simulating Key Generation and Verification:\n");
    int allMatch = 1;
    for (int r = 1; r <= 16; r++) {
        currC = rotr28(currC, decShifts[r-1]);
        currD = rotr28(currD, decShifts[r-1]);
        C_dec[r] = currC;
        D_dec[r] = currD;

        int targetRound = 17 - r;
        if (C_dec[r] == C_enc[targetRound] && D_dec[r] == D_enc[targetRound]) {
            printf("  Dec Round %2d generates K%02d: MATCH (C=0x%07X, D=0x%07X)\n",
                   r, targetRound, C_dec[r], D_dec[r]);
        } else {
            printf("  Dec Round %2d MISMATCH!\n", r);
            allMatch = 0;
        }
    }

    if (allMatch) {
        printf("\nSUCCESS: All 16 decryption subkeys generated in exact reverse order!\n");
    }

    return 0;
}
