#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Simple reversible Feistel block cipher for demonstration
uint64_t dummyDES(uint64_t block, uint64_t key, int encrypt) {
    uint32_t L = (uint32_t)(block >> 32);
    uint32_t R = (uint32_t)(block & 0xFFFFFFFF);
    uint32_t K = (uint32_t)(key & 0xFFFFFFFF);

    if (encrypt) {
        for (int r = 0; r < 4; r++) {
            uint32_t nextL = R;
            uint32_t f = R ^ (K + (uint32_t)r * 0x9E3779B9U);
            uint32_t nextR = L ^ f;
            L = nextL;
            R = nextR;
        }
        return (((uint64_t)L) << 32) | R;
    } else {
        // Reverse Feistel rounds
        for (int r = 3; r >= 0; r--) {
            uint32_t prevR = L;
            uint32_t f = L ^ (K + (uint32_t)r * 0x9E3779B9U);
            uint32_t prevL = R ^ f;
            L = prevL;
            R = prevR;
        }
        return (((uint64_t)L) << 32) | R;
    }
}

// 3DES (Triple DES) in EDE Mode (Encrypt-Decrypt-Encrypt)
uint64_t tripleDES_Encrypt(uint64_t block, uint64_t k1, uint64_t k2, uint64_t k3) {
    uint64_t c = dummyDES(block, k1, 1);
    c = dummyDES(c, k2, 0);
    c = dummyDES(c, k3, 1);
    return c;
}

uint64_t tripleDES_Decrypt(uint64_t block, uint64_t k1, uint64_t k2, uint64_t k3) {
    uint64_t p = dummyDES(block, k3, 0);
    p = dummyDES(p, k2, 1);
    p = dummyDES(p, k1, 0);
    return p;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 19: 3DES IN CIPHER BLOCK CHAINING (CBC) \n");
    printf("======================================================\n\n");

    uint64_t k1 = 0x133457799BBCDFF1ULL;
    uint64_t k2 = 0x0123456789ABCDEFULL;
    uint64_t k3 = 0xA5A5A5A55A5A5A5AULL;
    uint64_t IV = 0x1234567890ABCDEFULL;

    uint64_t plaintextBlocks[3] = {
        0x48656C6C6F20576FULL, // "Hello Wo"
        0x726C642120434243ULL, // "rld! CBC"
        0x2033444553202121ULL  // " 3DES !!"
    };

    printf("Initialization Vector (IV): 0x%016llX\n\n", IV);

    // CBC Encryption: C_i = E(P_i ^ C_{i-1})
    uint64_t cipherBlocks[3];
    uint64_t prev = IV;
    printf("Encrypting 3 blocks using 3DES-CBC:\n");
    for (int i = 0; i < 3; i++) {
        uint64_t xorInput = plaintextBlocks[i] ^ prev;
        cipherBlocks[i] = tripleDES_Encrypt(xorInput, k1, k2, k3);
        prev = cipherBlocks[i];
        printf("  Block %d: Plain = 0x%016llX -> Cipher = 0x%016llX\n",
               i + 1, plaintextBlocks[i], cipherBlocks[i]);
    }

    // CBC Decryption: P_i = D(C_i) ^ C_{i-1}
    uint64_t decryptedBlocks[3];
    prev = IV;
    printf("\nDecrypting 3 blocks using 3DES-CBC:\n");
    for (int i = 0; i < 3; i++) {
        uint64_t decOutput = tripleDES_Decrypt(cipherBlocks[i], k1, k2, k3);
        decryptedBlocks[i] = decOutput ^ prev;
        prev = cipherBlocks[i];
        printf("  Block %d: Cipher = 0x%016llX -> Recovered = 0x%016llX\n",
               i + 1, cipherBlocks[i], decryptedBlocks[i]);
    }

    printf("\n======================================================\n");
    printf("ANALYSIS QUESTIONS:\n");
    printf("a. For security, which would you choose (DES vs 3DES)?\n");
    printf("   Answer: Choose 3DES (or modern AES). Single DES has only a 56-bit key,\n");
    printf("   which can be cracked by exhaustive search in hours. 3DES provides 112 or\n");
    printf("   168 bits of key length, offering dramatically stronger security.\n\n");

    printf("b. For performance, which would you choose (DES vs 3DES)?\n");
    printf("   Answer: Choose Single DES (or AES). 3DES requires three consecutive block\n");
    printf("   cipher evaluations (Encrypt-Decrypt-Encrypt) per block, making it approximately\n");
    printf("   3 times slower than single DES in software execution.\n");
    printf("======================================================\n");

    return 0;
}
