# Experiment 6: Breaking an Affine Cipher

## Aim
To write a C program to cryptanalyze (break) an Affine Cipher given that the most frequent letter in the ciphertext is 'B' and the second most frequent letter is 'U'.

## Algorithm
1. Start the program.
2. Formulate system of congruences based on standard English frequencies ($E=4$, $T=19$) and observed ciphertext frequencies ($B=1$, $U=20$):
   $$\begin{aligned}
   (4a + b) &\equiv 1 \pmod{26} \\
   (19a + b) &\equiv 20 \pmod{26}
   \end{aligned}$$
3. Subtract the two equations:
   $$15a \equiv 19 \pmod{26}$$
4. Calculate multiplicative inverse of $15 \pmod{26}$, which is $7$ ($15 \times 7 = 105 \equiv 1 \pmod{26}$).
5. Multiply both sides by 7:
   $$a \equiv 19 \times 7 = 133 \equiv 3 \pmod{26}$$
6. Substitute $a=3$ into equation 1:
   $$4(3) + b \equiv 1 \pmod{26} \implies 12 + b \equiv 1 \implies b = -11 \equiv 15 \pmod{26}$$
7. Calculate $a^{-1} = 3^{-1} \equiv 9 \pmod{26}$.
8. Decrypt using $p = 9(C - 15) \pmod{26}$.
9. Stop.

## Sample Output
```text
Solved Key Parameters:
  Multiplicative Key (a) = 3
  Additive Shift (b)     = 15
  Decryption key (a^-1)  = 9 mod 26

Verification:
  E([3, 15], 'E'(4))  = (3*4 + 15) mod 26 = 1 ('B')
  E([3, 15], 'T'(19)) = (3*19 + 15) mod 26 = 20 ('U')

Decrypting ciphertext "B U B U":
Recovered plaintext:    "E T E T"
```
