#include <stdio.h>

// Greatest Common Divisor
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

// Modular inverse
long long modInverse(long long a, long long m) {
    a = (a % m + m) % m;
    for (long long x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}

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
    printf("   EXPERIMENT 25: RSA COMMON FACTOR VULNERABILITY     \n");
    printf("======================================================\n\n");

    printf("SCENARIO:\n");
    printf("- Modulus n = p * q, public key e.\n");
    printf("- An attacker possesses ciphertext blocks C_i without private key d.\n");
    printf("- Suppose someone leaks that a plaintext block M has a common factor with n.\n");
    printf("  Does this help the attacker?\n\n");

    // Concrete Example:
    long long p = 61, q = 53;
    long long n = p * q; // 3233
    long long phi = (p - 1) * (q - 1); // 3120
    long long e = 17;
    long long d = modInverse(e, phi);

    printf("Target Cryptosystem:\n");
    printf("  Public modulus n = %lld, e = %lld\n\n", n, e);

    // Suppose a message block M happens to share a factor with n (e.g. M is a multiple of p)
    long long M = 2 * p; // M = 122, shares factor p=61 with n
    long long C = modPow(M, e, n);

    printf("Vulnerable Plaintext Block M = %lld\n", M);
    printf("  Does gcd(M, n) > 1? gcd(%lld, %lld) = %lld\n", M, n, gcd(M, n));
    printf("Transmitted Ciphertext Block C = M^e mod n = %lld\n\n", C);

    printf("CRITICAL MATHEMATICAL FACT:\n");
    printf("  Since C = M^e mod n, any common factor of M and n is also a factor of C!\n");
    printf("  gcd(C, n) = gcd(M^e mod n, n) = gcd(M, n) = p\n\n");

    // The attacker only knows C and n:
    printf("ATTACK EXECUTION BY ADVERSARY:\n");
    long long recovered_p = gcd(C, n);
    long long recovered_q = n / recovered_p;

    printf("  Adversary computes gcd(C, n) = gcd(%lld, %lld) = %lld\n", C, n, recovered_p);
    printf("  Extracted Prime p = %lld\n", recovered_p);
    printf("  Extracted Prime q = n / p = %lld\n", recovered_q);

    // Now adversary derives private key d:
    long long cracked_phi = (recovered_p - 1) * (recovered_q - 1);
    long long cracked_d = modInverse(e, cracked_phi);

    printf("  Calculated phi(n) = %lld\n", cracked_phi);
    printf("  CRACKED Private Key d = %lld (Actual d = %lld)\n\n", cracked_d, d);

    printf("ANSWER:\n");
    printf("  YES! If a plaintext block shares a common factor with n, gcd(C, n) directly\n");
    printf("  reveals one of the prime factors of n! The adversary immediately factors n,\n");
    printf("  derives the private key d, and completely breaks the entire cryptosystem,\n");
    printf("  allowing decryption of ALL past and future ciphertext blocks!\n");

    return 0;
}
