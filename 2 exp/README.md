# Experiment 2: Monoalphabetic Substitution Cipher

## Aim
To write a C program to implement the Monoalphabetic Substitution Cipher that maps each letter of the plaintext alphabet to a single unique letter of the ciphertext alphabet.

## Algorithm
1. Start the program.
2. Define a substitution key of 26 distinct characters representing the mapping for 'A' through 'Z'.
3. Read the plaintext message.
4. For encryption:
   - For each character at position `i`, find its index in the standard alphabet (0 to 25).
   - Substitute the character with the character at that index from the substitution key, preserving case.
5. For decryption:
   - For each character in the ciphertext, locate its index in the substitution key.
   - Replace it with the corresponding letter from standard alphabet ('A' + index).
6. Display the ciphertext and decrypted plaintext.
7. Stop.

## Sample Input
```text
Enter plaintext: cryptography
```

## Sample Output
```text
Alphabet: abcdefghijklmnopqrstuvwxyz
Key:      QWERTYUIOPASDFGHJKLZXCVBNM

Ciphertext:     eksnzqikqnpa
Decrypted text: cryptography
```
