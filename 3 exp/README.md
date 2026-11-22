# Experiment 3: Playfair Cipher

## Aim
To write a C program to implement the Playfair Cipher, which uses a 5x5 matrix of letters constructed with a keyword to encrypt plaintext two letters at a time.

## Algorithm
1. Start the program.
2. Read a keyword from the user and construct the 5x5 key matrix:
   - Fill in unique letters of keyword (treating 'I' and 'J' as the same letter).
   - Fill the remaining cells with unused letters of the English alphabet.
3. Prepare the plaintext:
   - Remove spaces and non-alphabetic characters, convert to uppercase.
   - If two consecutive letters in a pair are identical, insert 'X' between them.
   - If total length is odd, append 'X' at the end.
4. Encrypt digraphs $(C_1, C_2)$ using Playfair rules:
   - Same Row: Replace each letter with the one to its right (wrapping around).
   - Same Column: Replace each letter with the one below it (wrapping around).
   - Rectangle: Replace each letter with the letter in the same row but in the other letter's column.
5. Decryption applies reverse shift: left for same row, up for same column, rectangle remains same.
6. Display matrix, ciphertext, and decrypted text.
7. Stop.

## Sample Input
```text
Enter keyword: MONARCHY
Enter plaintext: instruments
```

## Sample Output
```text
5x5 Playfair Key Matrix:
M O N A R 
C H Y B D 
E F G I K 
L P Q S T 
U V W X Z 

Formatted Text: INSTRUMENTSX
Ciphertext:     GATLMZCLRQTX
Decrypted text: INSTRUMENTSX
```
