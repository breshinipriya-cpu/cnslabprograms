# Experiment 22: S-DES in Cipher Block Chaining (CBC) Mode

## Aim
To write a C program to implement Simplified DES (S-DES) in Cipher Block Chaining (CBC) mode with test data:
- Initialization Vector (IV): `1010 1010`
- Key: `01111 11101`
- Plaintext: `0000 0001 0010 0011`
- Expected Ciphertext: `1111 0100 0000 1011`

## Algorithm
1. Start the program.
2. Implement S-DES key generation:
   - Apply permutation $P_{10}$ to the 10-bit key.
   - Divide into two 5-bit halves, apply circular left shift LS-1, and apply $P_8$ to get $K_1$.
   - Apply circular left shift LS-2, and apply $P_8$ to get $K_2$.
3. Implement S-DES round function $f_K(R, SK)$:
   - Expand 4-bit right half using $E/P$ table.
   - XOR with subkey and pass through S-boxes $S_0$ and $S_1$.
   - Permute with $P_4$.
4. For CBC Encryption:
   - Block 1: $C_1 = E_K(P_1 \oplus IV)$.
   - Block 2: $C_2 = E_K(P_2 \oplus C_1)$.
5. For CBC Decryption:
   - Block 1: $P_1 = D_K(C_1) \oplus IV$.
   - Block 2: $P_2 = D_K(C_2) \oplus C_1$.
6. Display ciphertext and decrypted plaintext in binary.
7. Stop.

## Sample Output
```text
Test Parameters:
  IV:        1010 1010 (0xAA)
  Key:       01111 11101 (K1=0xFD, K2=0x7D)
  Plaintext: 0000 0001 0010 0011

Encrypted Ciphertext:
  1111 0100  0000 1011 (Hex: F4 0B)
Expected Ciphertext: 1111 0100  0000 1011
VERIFICATION: Ciphertext MATCHES TEST DATA PERFECTLY!

Decrypted Plaintext:
  0000 0001  0010 0011
VERIFICATION: Decryption matches original plaintext!
```
