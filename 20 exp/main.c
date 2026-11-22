#include <stdio.h>
#include <stdint.h>

// Simple reversible block cipher dummy for demonstration
uint64_t cipherEncrypt(uint64_t p, uint64_t k) {
    return p ^ k;
}
uint64_t cipherDecrypt(uint64_t c, uint64_t k) {
    return c ^ k;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 20: ERROR PROPAGATION IN ECB VS CBC     \n");
    printf("======================================================\n\n");

    uint64_t key = 0xDEADBEEFCAFE0011ULL;
    uint64_t IV  = 0xA1B2C3D4E5F60718ULL;

    uint64_t P[4] = {
        0x1111111111111111ULL,
        0x2222222222222222ULL,
        0x3333333333333333ULL,
        0x4444444444444444ULL
    };

    // CBC Encryption
    uint64_t C[4];
    uint64_t prev = IV;
    for (int i = 0; i < 4; i++) {
        C[i] = cipherEncrypt(P[i] ^ prev, key);
        prev = C[i];
    }

    printf("--- PART (a): TRANSMISSION ERROR IN CIPHERTEXT C1 ---\n");
    printf("Original C1:  0x%016llX\n", C[0]);
    // Invert 1 bit in transmitted C1
    uint64_t C_corrupted[4];
    for (int i = 0; i < 4; i++) C_corrupted[i] = C[i];
    C_corrupted[0] ^= 0x01ULL; // 1-bit transmission error
    printf("Corrupted C1: 0x%016llX\n\n", C_corrupted[0]);

    // Receiver decrypts
    uint64_t P_recovered[4];
    prev = IV;
    for (int i = 0; i < 4; i++) {
        P_recovered[i] = cipherDecrypt(C_corrupted[i], key) ^ prev;
        prev = C_corrupted[i];
    }

    printf("Decrypted Plaintext at Receiver:\n");
    for (int i = 0; i < 4; i++) {
        int status = (P_recovered[i] == P[i]);
        printf("  P%d: 0x%016llX -> %s\n", i + 1, P_recovered[i], 
               status ? "CORRECT" : "CORRUPTED");
    }
    printf("\nQUESTION (a) ANSWER:\n");
    printf("Are any blocks beyond P2 affected?\n");
    printf("-> NO. P1 is completely corrupted because C1 was modified before decryption.\n");
    printf("-> P2 has the exact bit error where C1 was flipped (P2 = D(C2) ^ C1).\n");
    printf("-> P3 and P4 are 100%% CORRECT because C2, C3 are error-free. CBC recovers automatically!\n\n");

    printf("--- PART (b): SOURCE PLAINTEXT ERROR IN P1 ---\n");
    printf("Suppose an error occurs in the source plaintext P1 before encryption.\n");
    uint64_t P_src_corrupted[4];
    for (int i = 0; i < 4; i++) P_src_corrupted[i] = P[i];
    P_src_corrupted[0] ^= 0x01ULL; // Bit error in P1

    uint64_t C_cascade[4];
    prev = IV;
    for (int i = 0; i < 4; i++) {
        C_cascade[i] = cipherEncrypt(P_src_corrupted[i] ^ prev, key);
        prev = C_cascade[i];
    }

    printf("Ciphertext Propagation:\n");
    for (int i = 0; i < 4; i++) {
        printf("  C%d changed? %s\n", i + 1, (C_cascade[i] != C[i]) ? "YES (PROPAGATED)" : "NO");
    }

    printf("\nQUESTION (b) ANSWER:\n");
    printf("Through how many ciphertext blocks is this error propagated? What is the effect at the receiver?\n");
    printf("-> The error propagates through ALL subsequent ciphertext blocks (C1 to CN).\n");
    printf("-> At the receiver: The received ciphertext decrypts consistently to the source\n");
    printf("   plaintext blocks. Therefore, only P1 contains the source bit error; all\n");
    printf("   subsequent plaintext blocks P2..PN are decrypted without extra errors.\n");

    return 0;
}
