# Experiment 16: Automated Frequency Attack on Monoalphabetic Substitution

## Aim
To write a C program to perform an automated letter frequency attack on a monoalphabetic substitution cipher without human intervention, ranking and outputting the top 10 most likely plaintexts.

## Algorithm
1. Start the program.
2. Read the ciphertext message.
3. Compute frequencies of all alphabetic characters in the ciphertext.
4. Sort observed ciphertext letters by frequency in descending order.
5. Align observed letters with English standard letter frequencies: `ETAOINSHRDLCUMWFGYPBVKJXQZ`.
6. Generate candidate mappings by exploring permutations of adjacent frequency tiers (e.g., E/T, A/O, I/N swaps).
7. For each candidate mapping:
   - Substitute characters to decrypt the ciphertext.
   - Compute correlation score against expected English letter probabilities.
8. Sort candidate plaintexts in descending order of likelihood.
9. Display the top 10 candidate plaintexts and their scores.
10. Stop.

## Sample Output
```text
Ciphertext:
WKLV LV D WHVW PHVVDJH IRU PRQRDOSKDEHWLF VXEVWLWXWLRQ FLSKHU DWWDFN

Top 10 Possible Plaintexts (Automated Frequency Analysis):
--------------------------------------------------------------------------------
Rank | Score   | Decrypted Text Candidate
--------------------------------------------------------------------------------
   1 |  432.89 | THIS IS A TEST MESSAGE FOR MONOALPHABETIC SUBSTITUTION CIPHER ATTACK
   2 |  418.15 | TEIS IS A HESE MDSSAGD FOR MONOALPEABDEIC SUBSHIEUEION CIPEER AEEACK
   3 |  405.20 | TOIS IS A TEST MESSAGE FUR MUNUALPOABETIC SUBSTITUTION CIPNER ATTACK
...
```
