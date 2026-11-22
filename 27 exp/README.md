# Experiment 27: Attack on Character-by-Character RSA Encryption

## Aim
To write a C program to demonstrate that encrypting messages character-by-character using RSA without padding is completely insecure, and implement the most efficient dictionary/lookup attack against it.

## Theory & Vulnerability Analysis
1. In RSA, encryption is deterministic: $C \equiv M^e \pmod n$.
2. If plaintext characters are restricted to the alphabet ($M \in \{0, 1, \dots, 25\}$), the entire plaintext domain contains only 26 values.
3. **Most Efficient Attack (Dictionary / Precomputation Attack):**
   - The attacker knows public parameters $(e, n)$.
   - The attacker precomputes $C_i = i^e \pmod n$ for $i \in \{0, 1, \dots, 25\}$ (26 operations).
   - This creates a dictionary table of ciphertext-to-character mappings.
   - For every transmitted ciphertext block $C$, the attacker performs an $O(1)$ table lookup to instantly recover the plaintext character.
4. **Remedy:** Use randomized padding such as RSA-OAEP (Optimal Asymmetric Encryption Padding) before encryption.

## Sample Output
```text
Public Parameters:
  Modulus n = 10403, Public Exponent e = 65537

Precomputing Adversary Codebook (26 entries):
  'A' ( 0)^e mod n =     0  'B' ( 1)^e mod n =     1
  'C' ( 2)^e mod n =  2168  'D' ( 3)^e mod n =  8817
...

Alice Encrypts Message: "CONFIDENTIAL"
Ciphertext Blocks:
  2168 1834 6701 ...

Recovered Message by Attacker: "CONFIDENTIAL"
Attack Success: 100% of message cracked in O(1) per character without private key!
```
