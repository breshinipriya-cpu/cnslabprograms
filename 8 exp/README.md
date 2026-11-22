# Experiment 8: Keyword-Based Monoalphabetic Cipher

## Aim
To write a C program to implement a monoalphabetic substitution cipher generated using a keyword (e.g., "CIPHER") followed by the remaining unused letters in alphabetical order.

## Algorithm
1. Start the program.
2. Read the keyword from the user (default: `CIPHER`).
3. Construct the substitution alphabet:
   - Append each unique uppercase letter from the keyword.
   - Append all remaining unused letters of the alphabet in normal order (A to Z).
4. Display the mapping between plaintext alphabet and generated ciphertext alphabet.
5. Read plaintext from user.
6. Encrypt each letter by substituting it with the letter at the same index in the generated cipher alphabet.
7. Decrypt by mapping each ciphertext letter back to the original alphabet index.
8. Display ciphertext and decrypted plaintext.
9. Stop.

## Sample Input
```text
Enter keyword: CIPHER
Enter plaintext: hello world
```

## Sample Output
```text
plain:  a b c d e f g h i j k l m n o p q r s t u v w x y z
cipher: C I P H E R A B D F G J K L M N O Q S T U V W X Y Z 

Ciphertext:     dahhk vkChecked
Decrypted text: hello world
```
