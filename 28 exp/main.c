#include <stdio.h>

// Extended GCD to compute modular inverse
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
    printf("   EXPERIMENT 28: DIFFIE-HELLMAN VS LINEAR PROTOCOL   \n");
    printf("======================================================\n\n");

    long long q = 353; // Prime modulus
    long long a = 3;   // Public number

    printf("Public Parameters:\n");
    printf("  Modulus q = %lld, Public multiplier/base a = %lld\n\n", q, a);

    // --- PART 1: Flawed Scheme (Sending x * a mod q) ---
    printf("--- PART 1: FLAWED LINEAR SCHEME (Sending x * a mod q) ---\n");
    long long xA = 45; // Alice's secret
    long long xB = 89; // Bob's secret

    long long YA = (xA * a) % q; // Alice sends YA
    long long YB = (xB * a) % q; // Bob sends YB

    printf("Alice chooses secret xA = %lld, sends YA = xA * a mod q = %lld\n", xA, YA);
    printf("Bob chooses secret xB   = %lld, sends YB = xB * a mod q = %lld\n\n", xB, YB);

    // EVE'S ATTACK:
    printf("Eve's Attack on Linear Scheme:\n");
    long long a_inv = modInverse(a, q);
    printf("  Eve knows public a = %lld and prime q = %lld.\n", a, q);
    printf("  Eve computes modular inverse a^-1 mod q = %lld\n", a_inv);

    long long eve_xA = (YA * a_inv) % q;
    long long eve_xB = (YB * a_inv) % q;
    printf("  Eve extracts Alice's secret xA: YA * a^-1 mod q = (%lld * %lld) mod %lld = %lld\n",
           YA, a_inv, q, eve_xA);
    printf("  Eve extracts Bob's secret xB:   YB * a^-1 mod q = (%lld * %lld) mod %lld = %lld\n",
           YB, a_inv, q, eve_xB);

    printf("  Can Eve find the secret numbers? YES! Both xA and xB recovered directly!\n");
    printf("  Can Eve break the shared key?    YES! Eve computes K = xA * xB * a mod q = %lld\n\n",
           (eve_xA * eve_xB % q * a) % q);

    // --- PART 2: Secure Standard Diffie-Hellman Protocol ---
    printf("--- PART 2: SECURE DIFFIE-HELLMAN KEY EXCHANGE ---\n");
    printf("To securely agree on a key, Alice and Bob use MODULAR EXPONENTIATION:\n");
    long long alpha = 3; // Primitive root mod q
    long long dh_YA = modPow(alpha, xA, q); // a^xA mod q
    long long dh_YB = modPow(alpha, xB, q); // a^xB mod q

    printf("  Alice sends dh_YA = a^xA mod q = %lld\n", dh_YA);
    printf("  Bob sends dh_YB   = a^xB mod q = %lld\n", dh_YB);

    long long keyAlice = modPow(dh_YB, xA, q);
    long long keyBob   = modPow(dh_YA, xB, q);

    printf("  Alice computes Key K = (dh_YB)^xA mod q = %lld\n", keyAlice);
    printf("  Bob computes Key K   = (dh_YA)^xB mod q = %lld\n", keyBob);
    printf("  Shared secret matches: %s\n", (keyAlice == keyBob) ? "YES" : "NO");
    printf("  Security: Eve cannot recover xA or xB because Discrete Logarithm Problem\n");
    printf("            is computationally infeasible for large groups.\n");

    return 0;
}
