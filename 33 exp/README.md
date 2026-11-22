# Experiment 33: Data Encryption Standard (DES) Implementation

## Aim
To write a C program to implement the complete Data Encryption Standard (DES) algorithm encrypting and decrypting 64-bit blocks using a 56-bit key with 16 rounds of Feistel cipher.

## Algorithm
1. Start the program.
2. Initialize 64-bit key and compute 16 48-bit subkeys:
   - Permuted Choice 1 (PC-1) reduces 64 bits to 56 bits ($C_0, D_0$).
   - Apply circular left shifts according to the DES shift schedule.
   - Permuted Choice 2 (PC-2) selects 48 bits for each round subkey.
3. For 64-bit plaintext encryption:
   - Apply Initial Permutation (IP).
   - Divide into 32-bit left ($L_0$) and right ($R_0$) halves.
   - For rounds $r = 1 \dots 16$:
     - $L_r = R_{r-1}$
     - $R_r = L_{r-1} \oplus f(R_{r-1}, K_r)$
     - where $f(R, K)$ applies Expansion (E), XOR with $K_r$, S-box substitution (S1..S8), and Permutation (P).
   - Swap $L_{16}$ and $R_{16}$.
   - Apply Inverse Initial Permutation ($IP^{-1}$).
4. For decryption, execute the same process applying round keys in reverse order ($K_{16}$ to $K_1$).
5. Display ciphertext and decrypted block.
6. Stop.

## Sample Output
```text
Plaintext Block (64-bit): 0x0123456789ABCDEF
Key (64-bit with parity): 0x133457799BBCDFF1

Subkey Schedule Generated (16 rounds of 48-bit subkeys)
Encrypted Ciphertext (64-bit): 0x85E813540F0AB405
Decrypted Plaintext  (64-bit): 0x0123456789ABCDEF

VERIFICATION: Full DES Encryption and Decryption SUCCESSFUL!
```
