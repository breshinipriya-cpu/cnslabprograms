#include <stdio.h>
#include <string.h>

int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int invert2x2(int M[2][2], int inv[2][2]) {
    int det = (M[0][0] * M[1][1] - M[0][1] * M[1][0]) % 26;
    if (det < 0) det += 26;
    int det_inv = modInverse(det, 26);
    if (det_inv == -1) return 0;

    inv[0][0] = ( M[1][1] * det_inv) % 26;
    inv[0][1] = ((-M[0][1] + 26) * det_inv) % 26;
    inv[1][0] = ((-M[1][0] + 26) * det_inv) % 26;
    inv[1][1] = ( M[0][0] * det_inv) % 26;
    return 1;
}

void mul2x2(int A[2][2], int B[2][2], int R[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            R[i][j] = (A[i][0] * B[0][j] + A[i][1] * B[1][j]) % 26;
        }
    }
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 38: HILL CIPHER KNOWN & CHOSEN          \n");
    printf("                 PLAINTEXT ATTACK                     \n");
    printf("======================================================\n\n");

    // Secret Key Matrix K:
    int K[2][2] = {{9, 4}, {5, 7}};
    printf("Secret Key Matrix K:\n");
    printf("  [ %d  %d ]\n", K[0][0], K[0][1]);
    printf("  [ %d  %d ]\n\n", K[1][0], K[1][1]);

    // 1. KNOWN PLAINTEXT ATTACK
    printf("--- PART 1: KNOWN PLAINTEXT ATTACK ---\n");
    // Known plaintext blocks P = [FR, ID] = [[5, 17], [8, 3]]
    // det(P) = (5*3 - 17*8) = 15 - 136 = -121 = 9 mod 26, gcd(9, 26) = 1!
    int P[2][2] = {{5, 17}, {8, 3}};
    int C[2][2];
    mul2x2(P, K, C); // Intercepted Ciphertext blocks

    printf("Known Plaintext Matrix P:\n");
    printf("  [ %d  %d ] ('FR')\n", P[0][0], P[0][1]);
    printf("  [ %d  %d ] ('ID')\n\n", P[1][0], P[1][1]);

    printf("Corresponding Ciphertext Matrix C:\n");
    printf("  [ %d  %d ]\n", C[0][0], C[0][1]);
    printf("  [ %d  %d ]\n\n", C[1][0], C[1][1]);

    int P_inv[2][2];
    if (invert2x2(P, P_inv)) {
        int rec_K[2][2];
        mul2x2(P_inv, C, rec_K);
        printf("Calculated P^-1 mod 26:\n");
        printf("  [ %d  %d ]\n", P_inv[0][0], P_inv[0][1]);
        printf("  [ %d  %d ]\n\n", P_inv[1][0], P_inv[1][1]);

        printf("Recovered Key Matrix K = P^-1 * C mod 26:\n");
        printf("  [ %d  %d ]\n", rec_K[0][0], rec_K[0][1]);
        printf("  [ %d  %d ]\n", rec_K[1][0], rec_K[1][1]);

        if (rec_K[0][0] == K[0][0] && rec_K[0][1] == K[0][1] &&
            rec_K[1][0] == K[1][0] && rec_K[1][1] == K[1][1]) {
            printf("ATTACK RESULT: Secret Key Successfully Recovered!\n\n");
        }
    }

    // 2. CHOSEN PLAINTEXT ATTACK
    printf("--- PART 2: CHOSEN PLAINTEXT ATTACK ---\n");
    printf("Adversary chooses identity basis blocks P_chosen = I:\n");
    int I[2][2] = {{1, 0}, {0, 1}};
    int C_chosen[2][2];
    mul2x2(I, K, C_chosen);

    printf("Ciphertext for Chosen [1, 0]: [ %d, %d ] (Directly gives row 0 of K!)\n",
           C_chosen[0][0], C_chosen[0][1]);
    printf("Ciphertext for Chosen [0, 1]: [ %d, %d ] (Directly gives row 1 of K!)\n",
           C_chosen[1][0], C_chosen[1][1]);
    printf("ATTACK RESULT: Key directly extracted without any matrix inversion!\n");

    return 0;
}
