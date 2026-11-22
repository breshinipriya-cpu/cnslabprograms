#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Compute Greatest Common Divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Find modular multiplicative inverse of a modulo 26
int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Encrypt plaintext using Affine cipher C = (a*p + b) mod 26
void encryptAffine(const char p[], int a, int b, char c[]) {
    for (int i = 0; p[i] != '\0'; i++) {
        if (isupper(p[i])) {
            c[i] = ((a * (p[i] - 'A') + b) % 26) + 'A';
        } else if (islower(p[i])) {
            c[i] = ((a * (p[i] - 'a') + b) % 26) + 'a';
        } else {
            c[i] = p[i];
        }
    }
    c[strlen(p)] = '\0';
}

// Decrypt ciphertext using Affine cipher p = a^-1 * (C - b) mod 26
void decryptAffine(const char c[], int a, int b, char p[]) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) return;

    for (int i = 0; c[i] != '\0'; i++) {
        if (isupper(c[i])) {
            p[i] = ((a_inv * ((c[i] - 'A' - b + 26) % 26)) % 26) + 'A';
        } else if (islower(c[i])) {
            p[i] = ((a_inv * ((c[i] - 'a' - b + 26) % 26)) % 26) + 'a';
        } else {
            p[i] = c[i];
        }
    }
    p[strlen(c)] = '\0';
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 5: GENERALIZATION OF CAESAR (AFFINE)    \n");
    printf("======================================================\n");

    printf("\nPART (a): Limitations on value of b:\n");
    printf("- There are NO restrictions on b for one-to-one mapping.\n");
    printf("- b represents a cyclic shift and can be any integer from 0 to 25.\n");

    printf("\nPART (b): Allowed and Disallowed values of a:\n");
    printf("- For C = (a*p + b) mod 26 to be one-to-one, gcd(a, 26) MUST be 1.\n");
    printf("- Allowed values of a (coprime to 26): ");
    for (int i = 1; i < 26; i++) {
        if (gcd(i, 26) == 1) printf("%d ", i);
    }
    printf("\n- Disallowed values of a (gcd(a, 26) != 1): ");
    for (int i = 0; i < 26; i++) {
        if (gcd(i, 26) != 1) printf("%d ", i);
    }
    printf("\n\nDemonstration of collision for disallowed a = 2, b = 3:\n");
    printf("E([2, 3], p=0  ('A')) = (2*0 + 3) mod 26 = %d ('D')\n", (2*0 + 3) % 26);
    printf("E([2, 3], p=13 ('N')) = (2*13 + 3) mod 26 = %d ('D')\n", (2*13 + 3) % 26);
    printf("Both 'A' and 'N' map to 'D', proving decryption is impossible!\n");

    // Interactive encryption/decryption demonstration
    int a = 7, b = 3;
    char text[256] = "AFFINE CIPHER";
    char cipher[256];
    char decrypted[256];

    printf("\nDemonstration with valid key a = %d, b = %d:\n", a, b);
    printf("Plaintext:      %s\n", text);
    encryptAffine(text, a, b, cipher);
    printf("Ciphertext:     %s\n", cipher);
    decryptAffine(cipher, a, b, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
