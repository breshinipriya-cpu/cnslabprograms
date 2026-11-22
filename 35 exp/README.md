# Experiment 35: One-Time Pad Vigenère Cipher

## Aim
To write a C program to implement the One-Time Pad (OTP) version of the Vigenère cipher where the key is a random stream of numbers between 0 and 25 matching the length of the plaintext.

## Algorithm
1. Start the program.
2. Read the plaintext message.
3. Generate a non-repeating random key stream where each element $K_i \in [0, 25]$.
4. For encryption:
   - For each character $P_i$, compute:
     $$C_i = (P_i + K_i) \pmod{26}$$
   - Preserve non-alphabetic characters.
5. For decryption:
   - For each character $C_i$, compute:
     $$P_i = (C_i - K_i + 26) \pmod{26}$$
6. Display generated key stream, ciphertext, and recovered plaintext.
7. Stop.

## Sample Output
```text
Plaintext:  HELLO WORLD
Key Stream: 14 3 22 9 1 18 7 11 0 25 

Encrypted Ciphertext: VHONP OZWKC
Decrypted Plaintext:  HELLO WORLD

VERIFICATION: Decrypted text matches original plaintext!
```
