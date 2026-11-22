# Experiment 26: RSA Modulus Reuse After Key Compromise

## Aim
To write a C program to demonstrate that if an RSA user leaks their private key $d$, generating a new key pair $(e_2, d_2)$ while reusing the same modulus $n$ is completely insecure.

## Mathematical Working
1. In RSA, knowledge of $(n, e_1, d_1)$ provides a multiple of $\phi(n)$:
   $$k = e_1 d_1 - 1 = m \cdot \phi(n)$$
2. Given a multiple of $\phi(n)$ and $n = pq$, an adversary can efficiently factor $n$ into $p$ and $q$.
3. Once $p$ and $q$ are known, $\phi(n) = (p-1)(q-1)$ is known to the attacker forever.
4. If the user publishes a new public exponent $e_2$ using the same modulus $n$, the attacker simply computes:
   $$d_2 \equiv e_2^{-1} \pmod{\phi(n)}$$
5. The new private key is completely compromised.

## Sample Output
```text
Original Parameters:
  Modulus n = 4757, Public e1 = 101, Private d1 = 3221 (LEAKED!)

ATTACKER EXPLOITATION:
  Attacker knows: e1 * d1 - 1 = 325320 (Multiple of phi(n))
  Attacker factors modulus: p = 67, q = 71
  Attacker permanently knows phi(n) = 4620

Bob generates new key pair with SAME n:
  New public key e2 = 17
  Bob's new secret d2 = 3809

Attacker intercepts e2 and computes:
  d2_attacker = e2^-1 mod phi(n) = 3809
  Match? YES! KEY FULLY COMPROMISED!

CONCLUSION:
  It is COMPLETELY UNSAFE to reuse modulus n after a private key leak.
```
