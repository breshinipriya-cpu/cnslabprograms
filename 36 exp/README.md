# Experiment 36: Affine Caesar Cipher One-to-One Mapping Analysis

## Aim
To write a C program to demonstrate the Affine Caesar cipher $C = (ap + b) \pmod{26}$, prove that it is not one-to-one when $\gcd(a, 26) \ne 1$ (e.g., $a=2, b=3$ where $p=0$ and $p=13$ collide), and demonstrate valid one-to-one encryption and decryption when $\gcd(a, 26) = 1$.

## Theory
- For $C = (ap + b) \pmod{26}$ to be invertible, every plaintext letter must map to a unique ciphertext character.
- If $\gcd(a, 26) > 1$, then $a \cdot (26 / \gcd(a, 26)) \equiv 0 \pmod{26}$, causing collisions.
- For $a = 2, b = 3$:
  $$E([2, 3], 0) = (2 \cdot 0 + 3) \pmod{26} = 3 \text{ ('D')}$$
  $$E([2, 3], 13) = (2 \cdot 13 + 3) \pmod{26} = 29 \equiv 3 \pmod{26} \text{ ('D')}$$
  Since both 'A' and 'N' map to 'D', decryption is impossible.
- When $\gcd(a, 26) = 1$, $a^{-1} \pmod{26}$ exists and the mapping is strictly bijective.

## Sample Output
```text
1. DEMONSTRATION OF COLLISION (Disallowed a = 2, b = 3):
   gcd(2, 26) = 2 != 1 (NOT COPRIME)
   E([2, 3], 0  ('A')) = (2*0  + 3) mod 26 = 3 ('D')
   E([2, 3], 13 ('N')) = (2*13 + 3) mod 26 = 3 ('D')
   COLLISION CONFIRMED: Both 'A' and 'N' map to 'D'!

2. DEMONSTRATION OF VALID ONE-TO-ONE MAPPING (a = 7, b = 3):
   gcd(7, 26) = 1 (COPRIME)
   Multiplicative inverse a^-1 mod 26 = 15
   Plaintext:  AFFINE CIPHER
   Ciphertext: DMMHQF RHEAFS
   Decrypted:  AFFINE CIPHER (Exact one-to-one recovery!)
```
