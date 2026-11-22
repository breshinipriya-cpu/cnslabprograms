#include <stdio.h>
#include <string.h>

// Modular exponentiation
long long modPow(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 27: ATTACK ON CHARACTER-BY-CHARACTER    \n");
    printf("                     RSA ENCRYPTION                   \n");
    printf("======================================================\n\n");

    // Public parameters with large modulus n (factorization infeasible)
    long long n = 10403; // In practice large (e.g. 2048-bit), shown here with n > 26
    long long e = 65537;

    printf("Public Parameters:\n");
    printf("  Modulus n = %lld, Public Exponent e = %lld\n\n", n, e);

    printf("SCENARIO:\n");
    printf("Alice encrypts message character-by-character where each letter A-Z\n");
    printf("is encoded as 0 to 25, computing C = M^e mod n for each letter.\n");
    printf("QUESTION: Is this method secure? If not, what is the most efficient attack?\n\n");

    printf("ANSWER:\n");
    printf("  NO, THIS IS COMPLETELY INSECURE!\n");
    printf("  The plaintext space has only 26 possible values (0 to 25).\n");
    printf("  The most efficient attack is a DICTIONARY / CODEBOOK ATTACK (Precomputation).\n");
    printf("  The adversary computes C_i = i^e mod n for all 26 letters (taking < 1 ms),\n");
    printf("  and looks up intercepted ciphertexts to decrypt with zero key knowledge!\n\n");

    // Precomputing Dictionary / Codebook
    long long codebook[26];
    printf("Precomputing Adversary Codebook (26 entries):\n");
    for (int i = 0; i < 26; i++) {
        codebook[i] = modPow(i, e, n);
    }
    for (int i = 0; i < 26; i++) {
        printf("  '%c' (%2d)^e mod n = %5lld", 'A' + i, i, codebook[i]);
        if ((i + 1) % 2 == 0) printf("\n");
    }
    printf("\n");

    // Alice sends secret message "CONFIDENTIAL"
    const char *secret = "CONFIDENTIAL";
    int len = strlen(secret);
    long long ciphertext[32];

    printf("Alice Encrypts Message: \"%s\"\nCiphertext Blocks:\n  ", secret);
    for (int i = 0; i < len; i++) {
        int m = secret[i] - 'A';
        ciphertext[i] = modPow(m, e, n);
        printf("%lld ", ciphertext[i]);
    }
    printf("\n\n");

    // Adversary intercepts ciphertext and decrypts via table lookup
    printf("Adversary Interception & Table Lookup Attack:\n");
    char recovered[32];
    for (int i = 0; i < len; i++) {
        long long c = ciphertext[i];
        recovered[i] = '?';
        for (int k = 0; k < 26; k++) {
            if (codebook[k] == c) {
                recovered[i] = 'A' + k;
                break;
            }
        }
    }
    recovered[len] = '\0';

    printf("Recovered Message by Attacker: \"%s\"\n", recovered);
    printf("Attack Success: 100%% of message cracked in O(1) per character without private key!\n");

    return 0;
}
