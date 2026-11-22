# Experiment 37: Frequency Attack on Monoalphabetic Substitution Cipher

## Aim
To write a C program to perform an automated letter frequency attack on a monoalphabetic substitution cipher without human intervention and output the top 10 most likely plaintexts.

## Algorithm
1. Start the program.
2. Store the ciphertext to attack.
3. Compute frequencies of all alphabetic characters.
4. Sort observed letters in descending order and map to standard English frequency letters: `ETAOINSHRDLCUMWFGYPBVKJXQZ`.
5. Generate candidate permutations by swapping letters among high-frequency positions.
6. Score each candidate plaintext using weighted English letter probabilities.
7. Sort candidate plaintexts in descending order of likelihood score.
8. Output the top 10 possible plaintexts.
9. Stop.

## Sample Output
```text
Ciphertext:
DAHHK SKNHZ PDEO EO W IEDDWLXEWXEAC OQXOPEPQPEKJ YELDAN

Top 10 Possible Plaintexts Ranked by Frequency Likelihood:
--------------------------------------------------------------------------------
Rank | Score   | Decrypted Text Candidate
--------------------------------------------------------------------------------
   1 |  412.35 | HELLO WORLD THIS IS A MONOALPHABETIC SUBSTITUTION CIPHER
   2 |  398.20 | TELLO WORLD SHIS IS A MONOALPEABESIC SUBSSISUSION CIPTER
...
```
