#include <stdio.h>
#include <stdint.h>

// CMAC Subkey Generation for 64-bit and 128-bit blocks (NIST SP 800-38B)

// 64-bit block subkey generation (Const = 0x1B)
void generateSubkeys64(uint64_t L, uint64_t *K1, uint64_t *K2) {
    uint64_t Rb = 0x1BULL; // x^64 + x^4 + x^3 + x + 1

    // If MSB(L) == 0: K1 = L << 1, else K1 = (L << 1) ^ Rb
    if ((L & 0x8000000000000000ULL) == 0) {
        *K1 = L << 1;
    } else {
        *K1 = (L << 1) ^ Rb;
    }

    // If MSB(K1) == 0: K2 = K1 << 1, else K2 = (K1 << 1) ^ Rb
    if ((*K1 & 0x8000000000000000ULL) == 0) {
        *K2 = *K1 << 1;
    } else {
        *K2 = (*K1 << 1) ^ Rb;
    }
}

// 128-bit block subkey generation (Const = 0x87)
typedef struct {
    uint64_t hi;
    uint64_t lo;
} uint128_t;

uint128_t shl128(uint128_t val) {
    uint128_t res;
    res.hi = (val.hi << 1) | (val.lo >> 63);
    res.lo = val.lo << 1;
    return res;
}

void generateSubkeys128(uint128_t L, uint128_t *K1, uint128_t *K2) {
    uint64_t Rb = 0x87ULL; // x^128 + x^7 + x^2 + x + 1

    int msb_L = (L.hi & 0x8000000000000000ULL) != 0;
    *K1 = shl128(L);
    if (msb_L) K1->lo ^= Rb;

    int msb_K1 = (K1->hi & 0x8000000000000000ULL) != 0;
    *K2 = shl128(*K1);
    if (msb_K1) K2->lo ^= Rb;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 31: CMAC SUBKEY GENERATION (64 & 128)   \n");
    printf("======================================================\n\n");

    printf("QUESTIONS ANSWERED:\n");
    printf("a. What constants are needed for block sizes of 64 and 128 bits?\n");
    printf("   - For 64-bit blocks:  Constant Rb = 0x1B (from x^64 + x^4 + x^3 + x + 1)\n");
    printf("   - For 128-bit blocks: Constant Rb = 0x87 (from x^128 + x^7 + x^2 + x + 1)\n\n");

    printf("b. How the left shift and XOR accomplishes the desired result:\n");
    printf("   - Left shifting by 1 bit corresponds to multiplication by x in GF(2^b).\n");
    printf("   - If the most significant bit (MSB) was 1, shifting causes an overflow\n");
    printf("     beyond degree b-1 (creating term x^b).\n");
    printf("   - XORing with Rb reduces the polynomial modulo the irreducible polynomial,\n");
    printf("     keeping the element strictly within the finite field GF(2^b).\n\n");

    // Demonstration for 64-bit block size
    printf("--- 1. 64-Bit Subkey Derivation Demo ---\n");
    uint64_t L64 = 0x48656C6C6F20576FULL; // Simulated L = CIPH_K(0)
    uint64_t K1_64, K2_64;
    generateSubkeys64(L64, &K1_64, &K2_64);

    printf("  L  = 0x%016llX (MSB = %d)\n", L64, (int)(L64 >> 63));
    printf("  K1 = 0x%016llX\n", K1_64);
    printf("  K2 = 0x%016llX\n\n", K2_64);

    // Demonstration for 128-bit block size
    printf("--- 2. 128-Bit Subkey Derivation Demo ---\n");
    uint128_t L128 = {0x8000000000000000ULL, 0x0000000000000001ULL};
    uint128_t K1_128, K2_128;
    generateSubkeys128(L128, &K1_128, &K2_128);

    printf("  L  = 0x%016llX%016llX (MSB = 1 -> triggers XOR)\n", L128.hi, L128.lo);
    printf("  K1 = 0x%016llX%016llX\n", K1_128.hi, K1_128.lo);
    printf("  K2 = 0x%016llX%016llX\n", K2_128.hi, K2_128.lo);

    return 0;
}
