# Experiment 14: One-Time Pad Vigenère Cipher

## Aim
To write a C program to implement the one-time pad (OTP) version of the Vigenère cipher:
- a. Encrypt the plaintext *"send more money"* with key stream: `9 0 1 7 23 15 21 14 11 11 2 8 9`.
- b. Using the generated ciphertext, find a new key stream so that it decrypts to *"cash not needed"*.

## Algorithm
1. Start the program.
2. For Part (a):
   - For each character $P_i$ in *"send more money"*, shift by key stream $K_i$:
     $$C_i = (P_i + K_i) \pmod{26}$$
   - Generate ciphertext string.
3. For Part (b):
   - We require $(C_i - K'_i) \equiv P'_{i} \pmod{26}$ where $P'$ is *"cash not needed"*.
   - Compute required key stream:
     $$K'_i = (C_i - P'_i) \pmod{26}$$
4. Decrypt using $K'_i$ to verify that *"cash not needed"* is recovered.
5. Display ciphertext, calculated key stream, and verified decryption.
6. Stop.

## Sample Output
```text
--- PART (a): Encryption of 'send more money' ---
Plaintext:  sendmoremoney
Key stream: 9 0 1 7 23 15 21 14 11 11 2 8 9 
Ciphertext: bftkjlzkznpgb

--- PART (b): Finding Key for 'cash not needed' ---
Desired Plaintext: cashnotneeded
Required Key Stream: 25 5 1 3 22 11 6 13 6 9 13 2 24 

Verification Decryption with Key 2:
Decrypted text: cashnotneeded
```
