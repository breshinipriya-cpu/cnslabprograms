#include <stdio.h>
#include <math.h>

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 11: PLAYFAIR CIPHER KEYSPACE ANALYSIS   \n");
    printf("======================================================\n\n");

    printf("Analysis of Possible Keys in Playfair Cipher:\n");
    printf("- The Playfair cipher uses a 5x5 grid containing 25 letters\n");
    printf("  (usually 'I' and 'J' share a cell).\n\n");

    // Total theoretical permutations = 25!
    double log2_25fact = 0.0;
    double fact25 = 1.0;
    for (int i = 1; i <= 25; i++) {
        log2_25fact += log2(i);
        fact25 *= i;
    }

    printf("PART 1: Total possible keys (ignoring identical encryption results):\n");
    printf("  Formula: 25!\n");
    printf("  25! = 15,511,210,043,330,985,984,000,000\n");
    printf("  Scientific notation: %.4e\n", fact25);
    printf("  Power of 2: 2^(%.2f) ≈ 2^%d\n\n", log2_25fact, (int)round(log2_25fact));

    // Effectively unique keys:
    // Any cyclic shift of rows (5 ways) or columns (5 ways) results in the
    // exact same relative positions and identical encryption: factor of 25.
    // Effectively unique keys = 25! / 25 = 24!
    double log2_24fact = 0.0;
    double fact24 = 1.0;
    for (int i = 1; i <= 24; i++) {
        log2_24fact += log2(i);
        fact24 *= i;
    }

    printf("PART (a): Effectively unique keys (accounting for equivalent keys):\n");
    printf("  - Shifting all rows cyclically (5 choices) does not change relative positions.\n");
    printf("  - Shifting all columns cyclically (5 choices) also preserves encryption.\n");
    printf("  - Total cyclic symmetries = 5 * 5 = 25 equivalent matrices per key.\n");
    printf("  Formula: 25! / 25 = 24!\n");
    printf("  24! = %.4e\n", fact24);
    printf("  Power of 2: 2^(%.2f) ≈ 2^%d\n\n", log2_24fact, (int)round(log2_24fact));

    // If horizontal/vertical reflections and diagonals are also considered
    double log2_refl = log2_24fact - log2(4.0);
    printf("  Further considering 4 planar rotations/reflections:\n");
    printf("  24! / 4 ≈ %.4e ≈ 2^(%.2f) ≈ 2^%d\n", fact24 / 4.0, log2_refl, (int)round(log2_refl));

    return 0;
}
