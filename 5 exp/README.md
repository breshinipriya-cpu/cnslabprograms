# Experiment 5: Affine Caesar Cipher Analysis

## Aim
To write a C program to analyze the generalization of the Caesar cipher (Affine Caesar Cipher $C = (ap + b) \pmod{26}$), determine the limitations on $b$, and find which values of $a$ are allowed and not allowed for a one-to-one mapping.

## Questions Answered
- **a. Are there any limitations on the value of $b$?**  
  No. The value of $b$ provides a simple additive shift. Any integer $b \in \{0, 1, \dots, 25\}$ produces a valid permutation as long as $a$ is coprime to 26.
- **b. Determine which values of $a$ are not allowed.**  
  For the function to be one-to-one (invertible), $\gcd(a, 26) = 1$.  
  - **Disallowed values of $a$:** Any value sharing common factors 2 or 13 with 26:  
    `{0, 2, 4, 6, 8, 10, 12, 13, 14, 16, 18, 20, 22, 24}`
  - **Allowed values of $a$:** `{1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25}` (12 total values).

## Algorithm
1. Start the program.
2. Output theoretical analysis for limitations on $b$.
3. Iterate values $a$ from 0 to 25 and check $\gcd(a, 26)$:
   - If $\gcd(a, 26) == 1$, classify as allowed.
   - Otherwise, classify as disallowed.
4. Demonstrate collision for disallowed $a=2, b=3$ where $p=0$ and $p=13$ both map to $C=3$.
5. Perform encryption and decryption using a valid key (e.g., $a=7, b=3$) to demonstrate correct one-to-one mapping.
6. Stop.

## Sample Output
```text
PART (a): Limitations on value of b:
- There are NO restrictions on b for one-to-one mapping.
- b represents a cyclic shift and can be any integer from 0 to 25.

PART (b): Allowed and Disallowed values of a:
- For C = (a*p + b) mod 26 to be one-to-one, gcd(a, 26) MUST be 1.
- Allowed values of a (coprime to 26): 1 3 5 7 9 11 15 17 19 21 23 25 
- Disallowed values of a (gcd(a, 26) != 1): 0 2 4 6 8 10 12 13 14 16 18 20 22 24 

Demonstration of collision for disallowed a = 2, b = 3:
E([2, 3], p=0  ('A')) = (2*0 + 3) mod 26 = 3 ('D')
E([2, 3], p=13 ('N')) = (2*13 + 3) mod 26 = 3 ('D')
Both 'A' and 'N' map to 'D', proving decryption is impossible!

Demonstration with valid key a = 7, b = 3:
Plaintext:      AFFINE CIPHER
Ciphertext:     VIIRWN RPUWNE
Decrypted text: AFFINE CIPHER
```
