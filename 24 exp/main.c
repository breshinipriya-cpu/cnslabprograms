#include <stdio.h>
#include <math.h>

// Extended Euclidean Algorithm to find modular inverse
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

// Modular exponentiation (base^exp mod mod)
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
    printf("   EXPERIMENT 24: RSA PRIVATE KEY CALCULATION         \n");
    printf("======================================================\n\n");

    long long e = 31;
    long long n = 3599;

    printf("Given Public Parameters:\n");
    printf("  Public Exponent e = %lld\n", e);
    printf("  Modulus n         = %lld\n\n", n);

    // Step 1: Trial-and-error to find p and q
    printf("Step 1: Factoring n = 3599 via trial:\n");
    long long p = 0, q = 0;
    long long limit = (long long)sqrt((double)n) + 1;

    for (long long i = 2; i <= limit; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    printf("  Found prime factors: p = %lld, q = %lld\n", p, q);
    printf("  Verification: %lld * %lld = %lld\n\n", p, q, p * q);

    // Step 2: Calculate phi(n)
    long long phi_n = (p - 1) * (q - 1);
    printf("Step 2: Euler's Totient phi(n):\n");
    printf("  phi(n) = (p - 1) * (q - 1) = (%lld - 1) * (%lld - 1)\n", p, q);
    printf("  phi(n) = %lld * %lld = %lld\n\n", p - 1, q - 1, phi_n);

    // Step 3: Find private key d using Extended Euclidean Algorithm
    printf("Step 3: Finding private key d = e^-1 mod phi(n):\n");
    printf("  Solving: %lld * d = 1 mod %lld\n", e, phi_n);
    long long d = modInverse(e, phi_n);
    printf("  Private key d = %lld\n", d);
    printf("  Check: (%lld * %lld) mod %lld = %lld\n\n", e, d, phi_n, (e * d) % phi_n);

    // Demonstration of Encryption and Decryption
    printf("Demonstration of RSA Encryption & Decryption:\n");
    long long M = 123; // Sample message
    long long C = modPow(M, e, n);
    long long recovered = modPow(C, d, n);

    printf("  Original Message M   = %lld\n", M);
    printf("  Ciphertext C = M^e %% n = %lld\n", C);
    printf("  Decrypted M  = C^d %% n = %lld\n", recovered);
    printf("  Result: %s\n", (M == recovered) ? "MATCH (SUCCESS)" : "MISMATCH");

    return 0;
}
