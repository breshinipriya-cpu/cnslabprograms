# Experiment 15: Frequency Attack on Additive Cipher

## Aim
To write a C program to perform a letter frequency attack on an additive (Caesar) cipher without human intervention and output the top 10 most likely plaintexts.

## Algorithm
1. Start the program.
2. Read or initialize the ciphertext.
3. For each candidate shift key $k \in \{0, 1, \dots, 25\}$:
   - Decrypt the ciphertext: $P_i = (C_i - k + 26) \pmod{26}$.
   - Compute letter frequencies of the decrypted text.
   - Calculate correlation score with standard English letter frequency table:
     $$\text{Score} = \sum_{c='A'}^{\text{'Z'}} f_{\text{observed}}(c) \times f_{\text{English}}(c)$$
4. Sort all 26 decrypted candidates in descending order of correlation score.
5. Display the top 10 ranked candidates with their key, score, and candidate plaintext.
6. Stop.

## Sample Output
```text
Ciphertext: KHOOR ZRUOG WKLV LV DQ DGGLWLYH FLSKHU WHVW PHVVDJH

Top 10 Most Likely Plaintexts:
--------------------------------------------------------------------------------
Rank | Key | Score   | Decrypted Text Preview
--------------------------------------------------------------------------------
   1 |   3 |  684.52 | HELLO WORLD THIS IS AN ADDITIVE CIPHER TEST MESSAGE
   2 |  13 |  412.30 | ROVVY GYBVN DRSC SC KX KNNSDSFO MszROB DOCD WOCCKGO
   3 |  21 |  398.11 | ZWDDG OWEPL LTAG AG SF SLLALANW UAHzWJ LWKL EWKKSYW
...
```
