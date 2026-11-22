#include <stdio.h>
#include <stdint.h>

// Simple 64-bit block cipher emulation for CBC-MAC demonstration
uint64_t blockCipher(uint64_t block, uint64_t key) {
    // 4-round Feistel permutation
    uint32_t L = (uint32_t)(block >> 32);
    uint32_t R = (uint32_t)(block & 0xFFFFFFFF);
    uint32_t K = (uint32_t)(key & 0xFFFFFFFF);

    for (int r = 0; r < 4; r++) {
        uint32_t nextL = R;
        uint32_t nextR = L ^ (R + K + (uint32_t)r * 0x9E3779B9U);
        L = nextL;
        R = nextR;
    }
    return (((uint64_t)L) << 32) | R;
}

// CBC-MAC for an array of 64-bit blocks
uint64_t computeCBC_MAC(const uint64_t blocks[], int numBlocks, uint64_t key) {
    uint64_t state = 0; // IV = 0 for standard CBC-MAC
    for (int i = 0; i < numBlocks; i++) {
        state = blockCipher(state ^ blocks[i], key);
    }
    return state;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 30: CBC-MAC ONE-BLOCK FORGERY ATTACK     \n");
    printf("======================================================\n\n");

    // Secret Key K known only to the sender/receiver
    uint64_t secretKey = 0xFEEDBEEF01234567ULL;

    // One-block message X
    uint64_t X = 0x4142434445464748ULL; // "ABCDEFGH"

    printf("1. Legitimate One-Block Message:\n");
    printf("   X = 0x%016llX\n", X);

    // Compute legitimate tag T = MAC(K, X)
    uint64_t T = computeCBC_MAC(&X, 1, secretKey);
    printf("   Tag T = MAC(K, X) = 0x%016llX\n\n", T);

    // ADVERSARY FORGERY ATTACK:
    // Adversary constructs a 2-block message: M_forged = X || (X ^ T)
    // Without knowing K!
    printf("2. Adversary Constructs Forged Two-Block Message:\n");
    uint64_t block1 = X;
    uint64_t block2 = X ^ T;
    uint64_t forgedMsg[2] = {block1, block2};

    printf("   Block 1: X         = 0x%016llX\n", block1);
    printf("   Block 2: X XOR T   = 0x%016llX\n\n", block2);

    // Mathematical verification of CBC-MAC calculation:
    // Block 1: C1 = E_K(0 ^ X) = E_K(X) = T
    // Block 2: C2 = E_K(C1 ^ Block2) = E_K(T ^ (X ^ T)) = E_K(X) = T!
    uint64_t forgedTag = computeCBC_MAC(forgedMsg, 2, secretKey);

    printf("3. Verification of Forged Tag:\n");
    printf("   MAC(K, X || (X XOR T)) = 0x%016llX\n", forgedTag);
    printf("   Original Tag T         = 0x%016llX\n\n", T);

    if (forgedTag == T) {
        printf("RESULT: FORGERY ATTACK SUCCESSFUL!\n");
        printf("The adversary successfully forged a valid MAC for a 2-block message\n");
        printf("without possessing the secret key K!\n");
    } else {
        printf("Forgery failed.\n");
    }

    return 0;
}
