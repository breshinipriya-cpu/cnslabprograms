# Experiment 10: Playfair Cipher with Given Matrix

## Aim
To write a C program to encrypt the message *"Must see you over Cadogan West. Coming at once."* using the given 5x5 Playfair matrix:
```text
M F H I/J K
U N O P   Q
Z V W X   Y
E L A R   G
D S T B   C
```

## Algorithm
1. Start the program.
2. Initialize the 5x5 Playfair matrix as specified in the problem statement.
3. Prepare the plaintext:
   - Convert letters to uppercase and remove whitespace and punctuation.
   - Insert filler 'X' between identical letters in a digraph (e.g., "EE" -> "EX E").
   - Pad with 'X' at the end if the number of letters is odd.
4. For each pair $(P_1, P_2)$:
   - Same row: shift each letter right by 1 position (modulo 5).
   - Same column: shift each letter down by 1 position (modulo 5).
   - Rectangle: swap column coordinates.
5. Display formatted digraphs and the encrypted ciphertext.
6. Stop.

## Sample Output
```text
Given Playfair Matrix:
M F H I K 
U N O P Q 
Z V W X Y 
E L A R G 
D S T B C 

Original Message: Must see you over Cadogan West. Coming at once.
Formatted Digraphs: MUSTSEXEYOUOVERCADOGANWESTCOMINGATONCEX

Ciphertext: UZ TU RZ EX OU PW ER DA TG ER EX TB HM PO DA EX 
Concatenated Ciphertext: UZTURZEXOUPWERDATGEREXTBHMPO DAEX
```
