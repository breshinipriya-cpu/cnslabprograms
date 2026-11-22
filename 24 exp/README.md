# Experiment 24: RSA Private Key Calculation

## Aim
To write a C program to determine the private key of an RSA cryptosystem with public key $e = 31, n = 3599$ by finding prime factors $p$ and $q$ and applying the Extended Euclidean Algorithm to calculate the multiplicative inverse of $31 \pmod{\phi(n)}$.

## Mathematical Working
1. **Factorization of $n = 3599$:**
   $$\sqrt{3599} \approx 59.99 \implies 60^2 - 1 = (60 - 1)(60 + 1) = 59 \times 61$$
   $$p = 59, \quad q = 61$$
2. **Euler's Totient $\phi(n)$:**
   $$\phi(n) = (p - 1)(q - 1) = 58 \times 60 = 3480$$
3. **Private Key $d$ using Extended Euclidean Algorithm:**
   $$31 \cdot d \equiv 1 \pmod{3480}$$
   $$3480 = 112(31) + 8$$
   $$31 = 3(8) + 7$$
   $$8 = 1(7) + 1$$
   Back-substituting gives $1 = 4(3480) - 449(31) \implies d \equiv -449 \equiv 3031 \pmod{3480}$.
   $$d = 3031$$
4. **Verification:**
   $$(31 \times 3031) \pmod{3480} = 93961 \pmod{3480} = 1$$

## Sample Output
```text
Given Public Parameters:
  Public Exponent e = 31
  Modulus n         = 3599

Step 1: Factoring n = 3599 via trial:
  Found prime factors: p = 59, q = 61

Step 2: Euler's Totient phi(n):
  phi(n) = 3480

Step 3: Finding private key d = e^-1 mod phi(n):
  Private key d = 3031

Demonstration of RSA Encryption & Decryption:
  Original Message M   = 123
  Ciphertext C = M^e % n = 850
  Decrypted M  = C^d % n = 123
  Result: MATCH (SUCCESS)
```
