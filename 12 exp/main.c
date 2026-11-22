#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Extended Euclidean Algorithm to find modular inverse
int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 12: HILL CIPHER (2x2 MATRIX)            \n");
    printf("======================================================\n\n");

    // Key Matrix K:
    // [ 9  4 ]
    // [ 5  7 ]
    int K[2][2] = {{9, 4}, {5, 7}};
    printf("Encryption Key Matrix K:\n");
    printf("  [ %d  %d ]\n", K[0][0], K[0][1]);
    printf("  [ %d  %d ]\n\n", K[1][0], K[1][1]);

    // Step 1: Determinant
    int det = (K[0][0] * K[1][1] - K[0][1] * K[1][0]) % 26;
    if (det < 0) det += 26;
    printf("Determinant of K = (9*7 - 4*5) mod 26 = 43 mod 26 = %d\n", det);

    // Step 2: Inverse of determinant
    int det_inv = modInverse(det, 26);
    printf("det^-1 mod 26 = %d (since %d * %d mod 26 = %d)\n\n", det_inv, det, det_inv, (det * det_inv) % 26);

    // Step 3: Inverse Key Matrix K^-1 = det^-1 * adj(K) mod 26
    // adj(K) = [ d  -b ]
    //          [ -c  a ]
    int adj[2][2] = {
        {K[1][1], (-K[0][1] + 26) % 26},
        {(-K[1][0] + 26) % 26, K[0][0]}
    };

    int K_inv[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            K_inv[i][j] = (det_inv * adj[i][j]) % 26;
        }
    }

    printf("Calculations for Inverse Key Matrix K^-1:\n");
    printf("  adj(K) = [ %d  %d ]\n", adj[0][0], adj[0][1]);
    printf("           [ %d  %d ]\n", adj[1][0], adj[1][1]);
    printf("  K^-1   = %d * adj(K) mod 26 = [ %d  %d ]\n", det_inv, K_inv[0][0], K_inv[0][1]);
    printf("                                [ %d  %d ]\n\n", K_inv[1][0], K_inv[1][1]);

    // Message to encrypt
    const char *rawMessage = "meet me at the usual place at ten rather than eight oclock";
    char plain[256];
    int plen = 0;
    for (int i = 0; rawMessage[i] != '\0'; i++) {
        if (isalpha(rawMessage[i])) {
            plain[plen++] = toupper(rawMessage[i]);
        }
    }
    if (plen % 2 != 0) {
        plain[plen++] = 'X'; // Pad if odd
    }
    plain[plen] = '\0';

    printf("Plaintext message: \"%s\"\n", rawMessage);
    printf("Formatted message: \"%s\" (Length: %d)\n\n", plain, plen);

    // Part (a): Encryption calculations
    char cipher[256];
    for (int i = 0; i < plen; i += 2) {
        int p1 = plain[i] - 'A';
        int p2 = plain[i + 1] - 'A';
        int c1 = (p1 * K[0][0] + p2 * K[1][0]) % 26;
        int c2 = (p1 * K[0][1] + p2 * K[1][1]) % 26;
        cipher[i] = c1 + 'A';
        cipher[i + 1] = c2 + 'A';
    }
    cipher[plen] = '\0';

    printf("PART (a): Ciphertext Result:\n");
    printf("  %s\n\n", cipher);

    // Part (b): Decryption calculations
    char decrypted[256];
    for (int i = 0; i < plen; i += 2) {
        int c1 = cipher[i] - 'A';
        int c2 = cipher[i + 1] - 'A';
        int p1 = (c1 * K_inv[0][0] + c2 * K_inv[1][0]) % 26;
        int p2 = (c1 * K_inv[0][1] + c2 * K_inv[1][1]) % 26;
        decrypted[i] = p1 + 'A';
        decrypted[i + 1] = p2 + 'A';
    }
    decrypted[plen] = '\0';

    printf("PART (b): Decryption Recovery:\n");
    printf("  %s\n", decrypted);

    return 0;
}
