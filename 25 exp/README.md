# Experiment 25: RSA Common Factor Vulnerability Analysis

## Aim
To write a C program to analyze the vulnerability when a plaintext block in RSA shares a common factor with the modulus $n = pq$, and determine whether this allows an adversary to break the cryptosystem.

## Theory & Analysis
1. In RSA, $n = pq$ where $p$ and $q$ are distinct prime numbers.
2. If a plaintext block $M$ shares a common factor with $n$ and $1 < M < n$, then:
   $$\gcd(M, n) \in \{p, q\}$$
3. Because $C \equiv M^e \pmod n$, any factor dividing $M$ and $n$ also divides $C$:
   $$\gcd(C, n) = \gcd(M^e \pmod n, n) = \gcd(M, n) = p \text{ (or } q \text{)}$$
4. **Vulnerability Conclusion:**
   - The attacker does **not** even need the plaintext block $M$.
   - The attacker simply calculates $\gcd(C, n)$ from the publicly observed ciphertext block $C$ and public modulus $n$.
   - This directly yields prime factor $p$.
   - The attacker then computes $q = n/p$, $\phi(n) = (p-1)(q-1)$, and $d \equiv e^{-1} \pmod{\phi(n)}$, recovering the private key and breaking all messages.

## Sample Output
```text
Target Cryptosystem:
  Public modulus n = 3233, e = 17

Vulnerable Plaintext Block M = 122
  Does gcd(M, n) > 1? gcd(122, 3233) = 61
Transmitted Ciphertext Block C = M^e mod n = 427

ATTACK EXECUTION BY ADVERSARY:
  Adversary computes gcd(C, n) = gcd(427, 3233) = 61
  Extracted Prime p = 61
  Extracted Prime q = n / p = 53
  Calculated phi(n) = 3120
  CRACKED Private Key d = 2753 (Actual d = 2753)

ANSWER:
  YES! If a plaintext block shares a common factor with n, gcd(C, n) directly
  reveals one of the prime factors of n! The adversary immediately factors n,
  derives the private key d, and completely breaks the entire cryptosystem.
```
