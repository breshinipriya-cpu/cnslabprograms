# Experiment 23: S-DES in Counter (CTR) Mode

## Aim
To write a C program to implement Simplified DES (S-DES) in Counter (CTR) mode with test data:
- Counter starting at: `0000 0000`
- Key: `01111 11101`
- Plaintext: `0000 0001 0000 0010 0000 0100`
- Expected Ciphertext: `0011 1000 0100 1111 0011 0010`

## Algorithm
1. Start the program.
2. Initialize 10-bit key and derive S-DES subkeys $K_1$ and $K_2$.
3. For Counter (CTR) mode encryption of block $i$ (with counter $T_i$ starting at 0):
   - Encrypt the counter using S-DES: $O_i = E_K(T_i)$.
   - Compute ciphertext block: $C_i = P_i \oplus O_i$.
   - Increment counter $T_{i+1} = T_i + 1$.
4. For CTR mode decryption of block $i$:
   - Encrypt the counter: $O_i = E_K(T_i)$.
   - Compute recovered plaintext: $P_i = C_i \oplus O_i$.
5. Verify matching against expected test vector.
6. Stop.

## Sample Output
```text
Test Parameters:
  Starting Counter: 0000 0000
  Key:              01111 11101
  Plaintext:        0000 0001  0000 0010  0000 0100

CTR Encryption Steps:
  Block 1: CTR=0000 0000 -> E(CTR)=0011 1001 -> Cipher=0011 1000 (0x38)
  Block 2: CTR=0000 0001 -> E(CTR)=0100 1101 -> Cipher=0100 1111 (0x4F)
  Block 3: CTR=0000 0010 -> E(CTR)=0011 0110 -> Cipher=0011 0010 (0x32)

Resulting Ciphertext:
  0011 1000  0100 1111  0011 0010
Expected Ciphertext:   0011 1000  0100 1111  0011 0010
VERIFICATION: Ciphertext MATCHES TEST DATA PERFECTLY!

CTR Decryption:
  0000 0001  0000 0010  0000 0100
VERIFICATION: Decryption recovered original plaintext!
```
