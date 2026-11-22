# Experiment 39: Automated Frequency Attack on Additive Cipher

## Aim
To write a C program to perform an automated letter frequency attack on an additive cipher without human intervention and output the top 10 most likely plaintexts.

## Algorithm
1. Start the program.
2. Store or input ciphertext encrypted with an unknown additive shift $k$.
3. For each candidate shift key $k \in \{0, 1, \dots, 25\}$:
   - Decrypt ciphertext characters: $P_i = (C_i - k + 26) \pmod{26}$.
   - Count frequencies of all 26 alphabetic characters in the candidate plaintext.
   - Calculate correlation score against standard English letter frequencies.
4. Sort all 26 candidate outputs in descending order of correlation score.
5. Display the top 10 candidate plaintexts.
6. Stop.

## Sample Output
```text
Ciphertext: LIPPS ASVPH XLMW MW ER EHHMXMZI GMTLIV EXXEGO XIWX

Top 10 Most Likely Plaintexts (Ranked Automatically):
--------------------------------------------------------------------------------
Rank | Shift | Score   | Decrypted Text Candidate
--------------------------------------------------------------------------------
   1 |    4  |  654.21 | HELLO WORLD THIS IS AN ADDITIVE CIPHER ATTACK TEST
   2 |   14  |  412.30 | XUBBE MEHBT JXYI YI QD QTTYJYLU IYFXUH QJJQSA JUIJ
   3 |    8  |  398.11 | DAHHK SKNHZ PDEO EO WJ WZZEPERA YELDAN WPPWYG PAOP
...
```
