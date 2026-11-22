#include <stdio.h>
#include <string.h>

// Extended Euclidean algorithm to find modular inverse
int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

// Invert 2x2 matrix modulo 26
int invert2x2(int M[2][2], int inv[2][2]) {
    int det = (M[0][0] * M[1][1] - M[0][1] * M[1][0]) % 26;
    if (det < 0) det += 26;
    int det_inv = modInverse(det, 26);
    if (det_inv == -1) return 0; // Not invertible

    inv[0][0] = ( M[1][1] * det_inv) % 26;
    inv[0][1] = ((-M[0][1] + 26) * det_inv) % 26;
    inv[1][0] = ((-M[1][0] + 26) * det_inv) % 26;
    inv[1][1] = ( M[0][0] * det_inv) % 26;
    return 1;
}

// Multiply 2x2 matrices modulo 26: R = A * B mod 26
void mul2x2(int A[2][2], int B[2][2], int R[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            R[i][j] = (A[i][0] * B[0][j] + A[i][1] * B[1][j]) % 26;
        }
    }
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 13: KNOWN & CHOSEN PLAINTEXT ATTACK     \n");
    printf("               ON 2x2 HILL CIPHER                     \n");
    printf("======================================================\n\n");

    // Secret Key Matrix K
    int K[2][2] = {{9, 4}, {5, 7}};
    printf("Secret Key Matrix K:\n");
    printf("  [ %d  %d ]\n", K[0][0], K[0][1]);
    printf("  [ %d  %d ]\n\n", K[1][0], K[1][1]);

    // 1. KNOWN PLAINTEXT ATTACK
    printf("--- PART 1: KNOWN PLAINTEXT ATTACK ---\n");
    // Suppose attacker discovers two plaintext pairs: "FR" (5, 17) and "ID" (8, 3)
    // Plaintext matrix P:
    // row 0 = "FR" = [5, 17]
    // row 1 = "ID" = [8,  3]
    int P[2][2] = {{5, 17}, {8, 3}};
    int C[2][2];
    mul2x2(P, K, C);

    printf("Attacker knows Plaintext-Ciphertext pairs:\n");
    printf("  P1 = (%d, %d) -> C1 = (%d, %d)\n", P[0][0], P[0][1], C[0][0], C[0][1]);
    printf("  P2 = (%d, %d) -> C2 = (%d, %d)\n\n", P[1][0], P[1][1], C[1][0], C[1][1]);

    // Since C = P * K mod 26, if P is invertible:
    // K = P^-1 * C mod 26
    int P_inv[2][2];
    if (invert2x2(P, P_inv)) {
        int recovered_K[2][2];
        mul2x2(P_inv, C, recovered_K);
        printf("P is invertible modulo 26! Calculating K = P^-1 * C mod 26:\n");
        printf("Recovered Key Matrix:\n");
        printf("  [ %d  %d ]\n", recovered_K[0][0], recovered_K[0][1]);
        printf("  [ %d  %d ]\n", recovered_K[1][0], recovered_K[1][1]);
        printf("Attack Status: KEY SUCCESSFULLY RECOVERED!\n\n");
    } else {
        printf("P is not invertible, different known pair required.\n\n");
    }

    // 2. CHOSEN PLAINTEXT ATTACK
    printf("--- PART 2: CHOSEN PLAINTEXT ATTACK ---\n");
    printf("In a chosen plaintext attack, the attacker chooses standard basis vectors:\n");
    printf("  Chosen Block 1 = [ 1, 0 ] ('BA')\n");
    printf("  Chosen Block 2 = [ 0, 1 ] ('AB')\n");
    printf("Matrix P = Identity Matrix I = [ 1  0 ]\n");
    printf("                               [ 0  1 ]\n");
    int P_chosen[2][2] = {{1, 0}, {0, 1}};
    int C_chosen[2][2];
    mul2x2(P_chosen, K, C_chosen);

    printf("Resulting Ciphertext Blocks directly reveal the key rows!\n");
    printf("  C1 = [1, 0] * K = [ %d, %d ] (Row 0 of K)\n", C_chosen[0][0], C_chosen[0][1]);
    printf("  C2 = [0, 1] * K = [ %d, %d ] (Row 1 of K)\n", C_chosen[1][0], C_chosen[1][1]);
    printf("Key extracted directly without matrix inversion!\n");

    return 0;
}
