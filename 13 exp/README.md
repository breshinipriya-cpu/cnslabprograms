# Experiment 13: Known Plaintext Attack on Hill Cipher

## Aim
To write a C program to demonstrate that the Hill cipher succumbs to a Known Plaintext Attack given sufficient plaintext-ciphertext pairs, and show that a Chosen Plaintext Attack makes recovery trivial.

## Theory & Algorithm
1. **Known Plaintext Attack:**
   - In Hill Cipher, encryption is linear: $C = P \cdot K \pmod{26}$.
   - Given $m$ known plaintext-ciphertext block pairs ($m \times m$ matrices $P$ and $C$):
     $$K = P^{-1} \cdot C \pmod{26}$$
   - If $\gcd(\det(P), 26) = 1$, matrix $P$ is invertible and key matrix $K$ is uniquely recovered.
2. **Chosen Plaintext Attack:**
   - Attacker chooses standard basis vectors $P = I_{m \times m}$ (e.g., $[1, 0]$ and $[0, 1]$).
   - Then $C = I \cdot K = K$.
   - The ciphertexts directly yield the rows of the key matrix without needing matrix inversion!

## Sample Output
```text
Secret Key Matrix K:
  [ 9  4 ]
  [ 5  7 ]

--- PART 1: KNOWN PLAINTEXT ATTACK ---
Attacker knows Plaintext-Ciphertext pairs:
  P1 = (12, 4) -> C1 = (24, 24)
  P2 = (4, 19) -> C2 = (1, 19)

P is invertible modulo 26! Calculating K = P^-1 * C mod 26:
Recovered Key Matrix:
  [ 9  4 ]
  [ 5  7 ]
Attack Status: KEY SUCCESSFULLY RECOVERED!

--- PART 2: CHOSEN PLAINTEXT ATTACK ---
Resulting Ciphertext Blocks directly reveal the key rows!
  C1 = [1, 0] * K = [ 9, 4 ] (Row 0 of K)
  C2 = [0, 1] * K = [ 5, 7 ] (Row 1 of K)
Key extracted directly without matrix inversion!
```
