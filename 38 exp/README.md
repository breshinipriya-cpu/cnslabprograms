# Experiment 38: Known and Chosen Plaintext Attacks on Hill Cipher

## Aim
To write a C program to implement both Known Plaintext Attack (KPA) and Chosen Plaintext Attack (CPA) on a $2 \times 2$ Hill Cipher.

## Theory & Algorithm
1. **Known Plaintext Attack:**
   - In Hill Cipher: $C = P \cdot K \pmod{26}$.
   - Given 2 pairs of known blocks forming invertible matrix $P$:
     $$K = P^{-1} \cdot C \pmod{26}$$
   - Calculate $\det(P)$, invert $\det(P)$ modulo 26, compute adjugate and inverse matrix $P^{-1}$.
   - Multiply $P^{-1} \cdot C \pmod{26}$ to extract key matrix $K$.
2. **Chosen Plaintext Attack:**
   - The attacker submits standard basis vectors: $P_1 = [1, 0]$ and $P_2 = [0, 1]$.
   - $C = I \cdot K = K$.
   - The resulting ciphertexts directly reveal the rows of secret matrix $K$ with zero computation.

## Sample Output
```text
Secret Key Matrix K:
  [ 9  4 ]
  [ 5  7 ]

--- PART 1: KNOWN PLAINTEXT ATTACK ---
Known Plaintext Matrix P:
  [ 5  17 ] ('FR')
  [ 8  3 ] ('ID')

Recovered Key Matrix K = P^-1 * C mod 26:
  [ 9  4 ]
  [ 5  7 ]
ATTACK RESULT: Secret Key Successfully Recovered!

--- PART 2: CHOSEN PLAINTEXT ATTACK ---
Ciphertext for Chosen [1, 0]: [ 9, 4 ] (Directly gives row 0 of K!)
Ciphertext for Chosen [0, 1]: [ 5, 7 ] (Directly gives row 1 of K!)
ATTACK RESULT: Key directly extracted without any matrix inversion!
```
