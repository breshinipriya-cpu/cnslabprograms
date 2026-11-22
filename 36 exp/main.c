#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

void encryptAffine(const char *in, int a, int b, char *out) {
    for (int i = 0; in[i] != '\0'; i++) {
        if (isupper(in[i])) {
            out[i] = ((a * (in[i] - 'A') + b) % 26) + 'A';
        } else if (islower(in[i])) {
            out[i] = ((a * (in[i] - 'a') + b) % 26) + 'a';
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

void decryptAffine(const char *in, int a, int b, char *out) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) return;
    for (int i = 0; in[i] != '\0'; i++) {
        if (isupper(in[i])) {
            out[i] = ((a_inv * ((in[i] - 'A' - b + 26) % 26)) % 26) + 'A';
        } else if (islower(in[i])) {
            out[i] = ((a_inv * ((in[i] - 'a' - b + 26) % 26)) % 26) + 'a';
        } else {
            out[i] = in[i];
        }
    }
    out[strlen(in)] = '\0';
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 36: AFFINE CIPHER ONE-TO-ONE ANALYSIS   \n");
    printf("======================================================\n\n");

    printf("Formula: C = E([a, b], p) = (a*p + b) mod 26\n");
    printf("Requirement: The mapping must be one-to-one (injective) so decryption is possible.\n\n");

    // Demonstration of disallowed key causing collision: a = 2, b = 3
    int a_bad = 2, b_bad = 3;
    printf("1. DEMONSTRATION OF COLLISION (Disallowed a = %d, b = %d):\n", a_bad, b_bad);
    printf("   gcd(%d, 26) = %d != 1 (NOT COPRIME)\n", a_bad, gcd(a_bad, 26));

    int c_0 = (a_bad * 0 + b_bad) % 26;   // p = 0 ('A')
    int c_13 = (a_bad * 13 + b_bad) % 26; // p = 13 ('N')
    printf("   E([%d, %d], 0  ('A')) = (%d*0  + %d) mod 26 = %d ('%c')\n",
           a_bad, b_bad, a_bad, b_bad, c_0, c_0 + 'A');
    printf("   E([%d, %d], 13 ('N')) = (%d*13 + %d) mod 26 = %d ('%c')\n",
           a_bad, b_bad, a_bad, b_bad, c_13, c_13 + 'A');
    printf("   COLLISION CONFIRMED: Both 'A' and 'N' map to '%c'!\n", c_0 + 'A');
    printf("   Decryption of '%c' is impossible (could be 'A' or 'N').\n\n", c_0 + 'A');

    // Demonstration of valid one-to-one key: a = 7, b = 3
    int a_good = 7, b_good = 3;
    printf("2. DEMONSTRATION OF VALID ONE-TO-ONE MAPPING (a = %d, b = %d):\n", a_good, b_good);
    printf("   gcd(%d, 26) = %d (COPRIME)\n", a_good, gcd(a_good, 26));
    int a_inv = modInverse(a_good, 26);
    printf("   Multiplicative inverse a^-1 mod 26 = %d\n", a_inv);

    char msg[128] = "AFFINE CIPHER";
    char cipher[128], decrypted[128];

    encryptAffine(msg, a_good, b_good, cipher);
    decryptAffine(cipher, a_good, b_good, decrypted);

    printf("   Plaintext:  %s\n", msg);
    printf("   Ciphertext: %s\n", cipher);
    printf("   Decrypted:  %s (Exact one-to-one recovery!)\n", decrypted);

    return 0;
}
