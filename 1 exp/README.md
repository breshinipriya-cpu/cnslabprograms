# Experiment 1: Caesar Cipher

## Aim
To write a C program to implement the Caesar Cipher substitution technique where each letter of the alphabet is replaced by another letter standing `k` places further down the alphabet, for `k` in the range 1 through 25.

## Algorithm
1. Start the program.
2. Read the plaintext message from the user.
3. Read the key `k` such that `1 <= k <= 25`.
4. For encryption:
   - For each uppercase character: `C = ((P - 'A') + k) % 26 + 'A'`
   - For each lowercase character: `C = ((P - 'a') + k) % 26 + 'a'`
   - Leave non-alphabetic characters unchanged.
5. For decryption:
   - For each uppercase character: `P = ((C - 'A') - k + 26) % 26 + 'A'`
   - For each lowercase character: `P = ((C - 'a') - k + 26) % 26 + 'a'`
6. Display the ciphertext and decrypted plaintext.
7. Stop.

## Sample Input
```text
Enter plaintext: Hello World
Enter key (1 - 25): 3
```

## Sample Output
```text
Ciphertext: Khoor Zruog
Decrypted text: Hello World
```
