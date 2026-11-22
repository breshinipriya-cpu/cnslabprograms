# Experiment 7: Substitution Cipher Cryptanalysis (The Gold-Bug)

## Aim
To write a C program to cryptanalyze and decrypt the classic substitution cipher from Edgar Allan Poe's "The Gold-Bug" using letter and word frequency analysis.

## Algorithm
1. Start the program.
2. Read or store the cipher text containing mysterious symbols.
3. Count the frequency of all symbols in the cipher text:
   - Identify symbol '8' as having the highest frequency, decoding to 'e'.
   - Identify the most common trigram ';48' which occurs repeatedly, matching the word "the".
   - Deduce ';' = 't', '4' = 'h', and '8' = 'e'.
4. Decipher the remaining letters by examining surrounding contexts and partial words.
5. Translate each symbol to its plaintext English character.
6. Display the frequency statistics and the full decrypted plaintext message.
7. Stop.

## Sample Output
```text
Top Frequencies in Ciphertext:
Symbol '8' count = 33
Symbol ';' count = 26
Symbol '4' count = 19
Trigram ';48' appears repeatedly -> stands for 'THE'

Decrypted Message:
a good glass in the bishop's hostel in the devil's seat forty-one degrees and thirteen minutes northeast and by north main branch seventh limb east side shoot from the left eye of the death's-head a bee line from the tree through the shot fifty feet out.
```
