#include <stdio.h>

// Extended GCD
long long extGCD(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
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

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 26: RSA REUSING MODULUS AFTER LEAK      \n");
    printf("======================================================\n\n");

    printf("SCENARIO:\n");
    printf("Bob leaks private key d1. Instead of generating a new modulus n,\n");
    printf("Bob generates a new public key e2 and private key d2 using the SAME n.\n");
    printf("QUESTION: Is this safe?\n\n");

    // Bob's original setup
    long long p = 67, q = 71;
    long long n = p * q; // 4757
    long long phi = (p - 1) * (q - 1); // 66 * 70 = 4620
    long long e1 = 101;
    long long d1 = modInverse(e1, phi); // 3221

    printf("Original Parameters:\n");
    printf("  Modulus n = %lld, Public e1 = %lld, Private d1 = %lld (LEAKED!)\n\n", n, e1, d1);

    // ATTACK: Once an attacker knows (n, e1, d1), e1*d1 - 1 is a multiple of phi(n)
    long long k = e1 * d1 - 1;
    printf("ATTACKER EXPLOITATION:\n");
    printf("  Attacker knows: e1 * d1 - 1 = %lld * %lld - 1 = %lld (Multiple of phi(n))\n", e1, d1, k);

    // Using knowledge of k to factor n:
    // For n = pq, (p+q) = n - phi(n) + 1. Since phi is a divisor of k:
    long long recovered_p = 0, recovered_q = 0;
    for (long long candidate_phi = phi; candidate_phi >= 2; candidate_phi--) {
        if (k % candidate_phi == 0) {
            // Check quadratic equation: x^2 - (n - phi + 1)x + n = 0
            long long s = n - candidate_phi + 1;
            long long disc = s * s - 4 * n;
            if (disc >= 0) {
                long long r = 0;
                while ((r + 1) * (r + 1) <= disc) r++;
                if (r * r == disc) {
                    recovered_p = (s - r) / 2;
                    recovered_q = (s + r) / 2;
                    if (recovered_p * recovered_q == n) break;
                }
            }
        }
    }

    printf("  Attacker factors modulus: p = %lld, q = %lld\n", recovered_p, recovered_q);
    long long recovered_phi = (recovered_p - 1) * (recovered_q - 1);
    printf("  Attacker permanently knows phi(n) = %lld\n\n", recovered_phi);

    // Now Bob chooses a "new" public key e2 with the same n:
    long long e2 = 17;
    long long d2_bob = modInverse(e2, phi);
    printf("Bob generates new key pair with SAME n:\n");
    printf("  New public key e2 = %lld\n", e2);
    printf("  Bob's new secret d2 = %lld\n\n", d2_bob);

    // Attacker calculates Bob's new private key directly:
    long long d2_attacker = modInverse(e2, recovered_phi);
    printf("Attacker intercepts e2 and computes:\n");
    printf("  d2_attacker = e2^-1 mod phi(n) = %lld\n", d2_attacker);
    printf("  Match? %s\n\n", (d2_attacker == d2_bob) ? "YES! KEY FULLY COMPROMISED!" : "NO");

    // Demonstration: Decrypting a secret sent to Bob under new key
    long long secretMsg = 999;
    long long C = modPow(secretMsg, e2, n);
    long long decryptedByAttacker = modPow(C, d2_attacker, n);
    printf("Secret sent to Bob under new e2: %lld (Ciphertext = %lld)\n", secretMsg, C);
    printf("Attacker decrypts using d2_attacker: %lld\n\n", decryptedByAttacker);

    printf("CONCLUSION:\n");
    printf("  It is COMPLETELY UNSAFE to reuse modulus n after a private key leak.\n");
    printf("  A compromised private key allows factoring the modulus n, which permanently\n");
    printf("  compromises any future key pair generated with that modulus!\n");

    return 0;
}
