# Experiment 19: 3DES in Cipher Block Chaining (CBC) Mode

## Aim
To write a C program to implement encryption and decryption in Cipher Block Chaining (CBC) mode using 3DES, and evaluate the trade-offs between DES and 3DES in terms of security and performance.

## Algorithm
1. Start the program.
2. Initialize 3DES keys ($K_1, K_2, K_3$) and 64-bit Initialization Vector ($IV$).
3. For CBC Encryption of block $i$:
   - $X_i = P_i \oplus C_{i-1}$ (where $C_0 = IV$).
   - $C_i = E_{K_3}(D_{K_2}(E_{K_1}(X_i)))$.
4. For CBC Decryption of block $i$:
   - $Y_i = D_{K_1}(E_{K_2}(D_{K_3}(C_i)))$.
   - $P_i = Y_i \oplus C_{i-1}$ (where $C_0 = IV$).
5. Compare DES and 3DES:
   - **Security:** 3DES is chosen because its 112/168-bit key protects against brute force, unlike DES's 56-bit key.
   - **Performance:** Single DES is chosen for raw speed because 3DES executes three encryption operations per block (approx 3x slower).
6. Stop.

## Sample Output
```text
Initialization Vector (IV): 0x1234567890ABCDEF

Encrypting 3 blocks using 3DES-CBC:
  Block 1: Plain = 0x48656C6C6F20576F -> Cipher = 0x2DE013FFC27A5B69
  Block 2: Plain = 0x726C642120434243 -> Cipher = 0x93309DEEF188DC13
  Block 3: Plain = 0x2033444553202121 -> Cipher = 0xBDFF426A5A6D51DE

Decrypting 3 blocks using 3DES-CBC:
  Block 1: Recovered = 0x48656C6C6F20576F (Matches original)
  Block 2: Recovered = 0x726C642120434243 (Matches original)
  Block 3: Recovered = 0x2033444553202121 (Matches original)
```
