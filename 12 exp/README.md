# Experiment 12: Hill Cipher (2x2 Matrix) Encryption & Decryption

## Aim
To write a C program to encrypt and decrypt the message *"meet me at the usual place at ten rather than eight oclock"* using the Hill cipher with key matrix:
$$K = \begin{pmatrix} 9 & 4 \\ 5 & 7 \end{pmatrix}$$

## Mathematical Working
1. **Determinant & Inversion:**
   $$\det(K) = (9 \times 7 - 4 \times 5) = 43 \equiv 17 \pmod{26}$$
   $$\det(K)^{-1} \equiv 17^{-1} \equiv 23 \pmod{26}$$
2. **Adjugate and Inverse Matrix:**
   $$\operatorname{adj}(K) = \begin{pmatrix} 7 & -4 \\ -5 & 9 \end{pmatrix} \equiv \begin{pmatrix} 7 & 22 \\ 21 & 9 \end{pmatrix} \pmod{26}$$
   $$K^{-1} = 23 \cdot \begin{pmatrix} 7 & 22 \\ 21 & 9 \end{pmatrix} \pmod{26} = \begin{pmatrix} 5 & 12 \\ 15 & 25 \end{pmatrix}$$
3. **Encryption:**
   $$(C_1, C_2) = (P_1, P_2) \cdot K \pmod{26}$$
4. **Decryption:**
   $$(P_1, P_2) = (C_1, C_2) \cdot K^{-1} \pmod{26}$$

## Sample Output
```text
Determinant of K = 17
det^-1 mod 26 = 23
Inverse Key Matrix K^-1:
  [ 5  12 ]
  [ 15 25 ]

Plaintext message: "meet me at the usual place at ten rather than eight oclock"
Formatted message: "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCKX"

PART (a): Ciphertext Result:
  UKLHEWWYFGYVHQHGUKLHEWWY...

PART (b): Decryption Recovery:
  MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCKX
```
