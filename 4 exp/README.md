# Experiment 4: Polyalphabetic Substitution Cipher (Vigenère Cipher)

## Aim
To write a C program to implement the Polyalphabetic Substitution Cipher (Vigenère Cipher) where a separate monoalphabetic substitution is used for each successive letter of the plaintext depending on a key.

## Algorithm
1. Start the program.
2. Read the plaintext message and keyword from the user.
3. For each alphabetic letter $P_i$ at index $i$:
   - Determine key letter $K_j$ by cycling through the keyword.
   - For encryption: $C_i = (P_i + K_j) \pmod{26}$.
   - For decryption: $P_i = (C_i - K_j + 26) \pmod{26}$.
4. Preserve case for uppercase and lowercase letters; keep punctuation and spaces intact.
5. Display the ciphertext and decrypted plaintext.
6. Stop.

## Sample Input
```text
Enter plaintext: GEORGETOWN
Enter key: KEY
```

## Sample Output
```text
Ciphertext:     QIENQIDYUL
Decrypted text: GEORGETOWN
```
