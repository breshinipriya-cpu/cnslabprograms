#include <stdio.h>

// Extended GCD to compute modular inverse
long long extGCD(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1; *y = 0; return a;
    }
    long long x1, y1;
    long long g = extGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

long long modInverse(long long a, long long m) {
    long long x, y;
    long long g = extGCD(a, m, &x, &y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}

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

// DSA Sign Simulation
void dsaSign(long long m, long long p, long long q, long long g, long long x,
             long long k, long long *r, long long *s) {
    *r = modPow(g, k, p) % q;
    long long k_inv = modInverse(k, q);
    *s = (k_inv * (m + x * (*r))) % q;
}

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 32: DSA VS RSA SIGNATURE IMPLICATIONS   \n");
    printf("======================================================\n\n");

    printf("Analysis of Nonce k in DSA vs Deterministic RSA:\n");
    printf("1. In RSA: Signature S = H(M)^d mod n is DETERMINISTIC.\n");
    printf("   Signing the same message twice always yields identical signatures.\n");
    printf("2. In DSA: Each signature generates a fresh random nonce k:\n");
    printf("   r = (g^k mod p) mod q, s = k^-1 * (H(M) + x*r) mod q.\n");
    printf("   Signing the same message twice yields DIFFERENT signatures.\n\n");

    // DSA Parameters
    long long p = 283;  // Prime modulus
    long long q = 47;   // Prime divisor of p-1
    long long g = 60;   // Generator (60^47 mod 283 = 1)
    long long x = 24;   // Private key

    long long M = 19;   // Message hash
    long long r1, s1, r2, s2;

    // Signing M with k = 15
    dsaSign(M, p, q, g, x, 15, &r1, &s1);
    // Signing SAME M with different k = 22
    dsaSign(M, p, q, g, x, 22, &r2, &s2);

    printf("Demonstrating Signature Variation on SAME Message M = %lld:\n", M);
    printf("  Signature 1 (with k=15): (r = %lld, s = %lld)\n", r1, s1);
    printf("  Signature 2 (with k=22): (r = %lld, s = %lld)\n", r2, s2);
    printf("  Result: Signatures are completely different!\n\n");

    // CATASTROPHIC IMPLICATION: Reusing k for two different messages
    printf("======================================================\n");
    printf("CRITICAL IMPLICATION: THE REUSED NONCE (k) DISASTER\n");
    printf("======================================================\n");
    printf("If an implementation reuses the same nonce k for two distinct messages M1 and M2:\n");

    long long M1 = 19;
    long long M2 = 33;
    long long reused_k = 15;

    long long ra, sa, rb, sb;
    dsaSign(M1, p, q, g, x, reused_k, &ra, &sa);
    dsaSign(M2, p, q, g, x, reused_k, &rb, &sb);

    printf("  Message 1: M1 = %lld -> Sig1: (r = %lld, s = %lld)\n", M1, ra, sa);
    printf("  Message 2: M2 = %lld -> Sig2: (r = %lld, s = %lld)\n", M2, rb, sb);
    printf("  Notice that r1 == r2 (%lld == %lld) because k was reused!\n\n", ra, rb);

    // ATTACKER PRIVATE KEY RECOVERY:
    // s1 - s2 = k^-1 * (M1 - M2) mod q
    // k = (M1 - M2) / (s1 - s2) mod q
    long long num = (M1 - M2 + q) % q;
    long long den = (sa - sb + q) % q;
    long long den_inv = modInverse(den, q);
    long long cracked_k = (num * den_inv) % q;

    // x = r^-1 * (s1 * k - M1) mod q
    long long r_inv = modInverse(ra, q);
    long long cracked_x = (r_inv * ((sa * cracked_k - M1) % q + q)) % q;

    printf("Adversary Attack:\n");
    printf("  Cracked Nonce k = %lld (Actual k = %lld)\n", cracked_k, reused_k);
    printf("  CRACKED PRIVATE KEY x = %lld (Actual x = %lld)\n\n", cracked_x, x);

    printf("CONCLUSION:\n");
    printf("  While randomized signatures prevent tracking and multiplicative attacks,\n");
    printf("  reusing nonce k even ONCE completely reveals the private key x!\n");

    return 0;
}
