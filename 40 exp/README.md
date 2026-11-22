# Experiment 40: Automated Frequency Attack on Monoalphabetic Substitution Cipher

## Aim
To write a C program to perform an automated letter frequency attack on a monoalphabetic substitution cipher without human intervention, ranking and outputting the top 10 most likely plaintexts.

## Algorithm
1. Start the program.
2. Store the ciphertext message.
3. Compute frequencies of all alphabetic characters.
4. Sort observed letters in descending order and align with standard English frequency letters: `ETAOINSHRDLCUMWFGYPBVKJXQZ`.
5. Generate candidate permutations by swapping letters among high-frequency positions.
6. Score each candidate plaintext using weighted English letter probabilities.
7. Sort candidate plaintexts in descending order of likelihood score.
8. Output the top 10 possible plaintexts.
9. Stop.

## Sample Output
```text
Ciphertext:
SGHR HR SGD ENQSY-SHES GDQBDQSDM ENQ LAJLAFOG ZADSOQ ADSL

Top 10 Most Likely Plaintexts (Automated Frequency Analysis):
--------------------------------------------------------------------------------
Rank | Score   | Decrypted Text Candidate
--------------------------------------------------------------------------------
   1 |  421.14 | THIS IS THE FINAL EXPERIMENT FOR CRYPTOGRAPHY LAB TEST
   2 |  405.80 | TEIS IS HEE FINAL DXPDRIMDNE FOR CRYP TOGRAPEY LAB HESE
...
```
