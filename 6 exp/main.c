#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Find modular multiplicative inverse
int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

// Decrypt affine ciphertext: p = a_inv * (c - b) mod 26
void decryptAffine(const char *c, int a_inv, int b, char *p) {
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
    printf("   EXPERIMENT 6: BREAKING AN AFFINE CIPHER            \n");
    printf("======================================================\n\n");

    printf("Given Cryptanalysis Information:\n");
    printf("- Most frequent ciphertext letter:      'B' (index 1)\n");
    printf("- Second most frequent ciphertext letter:'U' (index 20)\n");
    printf("- Most frequent English letter:         'E' (index 4)\n");
    printf("- Second most frequent English letter:  'T' (index 19)\n\n");

    printf("Setting up simultaneous modular congruences:\n");
    printf("  (a * 4  + b) mod 26 = 1    ... [Eq 1 for 'E' -> 'B']\n");
    printf("  (a * 19 + b) mod 26 = 20   ... [Eq 2 for 'T' -> 'U']\n\n");

    printf("Subtracting Eq 1 from Eq 2:\n");
    printf("  (19 - 4) * a = (20 - 1) mod 26\n");
    printf("  15 * a = 19 mod 26\n\n");

    int diff_p = 15;
    int diff_c = 19;
    int inv15 = modInverse(diff_p, 26);
    printf("Modular inverse of %d mod 26 = %d\n", diff_p, inv15);

    int a = (diff_c * inv15) % 26;
    int b = (1 - a * 4) % 26;
    if (b < 0) b += 26;

    printf("Solved Key Parameters:\n");
    printf("  Multiplicative Key (a) = %d\n", a);
    printf("  Additive Shift (b)     = %d\n", b);

    int a_inv = modInverse(a, 26);
    printf("  Decryption key (a^-1)  = %d mod 26\n\n", a_inv);

    printf("Verification:\n");
    printf("  E([%d, %d], 'E'(4))  = (%d*4 + %d) mod 26 = %d ('%c')\n", a, b, a, b, (a*4 + b)%26, (a*4 + b)%26 + 'A');
    printf("  E([%d, %d], 'T'(19)) = (%d*19 + %d) mod 26 = %d ('%c')\n\n", a, b, a, b, (a*19 + b)%26, (a*19 + b)%26 + 'A');

    // Decrypt a sample ciphertext created with this key
    char ciphertext[256] = "B U B U";
    char plaintext[256];
    decryptAffine(ciphertext, a_inv, b, plaintext);
    printf("Decrypting ciphertext \"%s\":\n", ciphertext);
    printf("Recovered plaintext:    \"%s\"\n", plaintext);

    return 0;
}
