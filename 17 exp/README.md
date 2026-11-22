# Experiment 17: DES Decryption Key Generation Scheme

## Aim
To write a C program to design a key-generation scheme with the appropriate shift schedule for the DES decryption process where 16 subkeys $(K_{16}, K_{15}, \dots, K_1)$ are used in reverse order.

## Theory & Shift Schedule Design
1. In encryption, the 56-bit key is split into two 28-bit halves ($C_0, D_0$).
2. Across 16 rounds, the total left shifts equal $4 \times 1 + 12 \times 2 = 28$ bits.
3. Because $28 \equiv 0 \pmod{28}$, after round 16, $C_{16} = C_0$ and $D_{16} = D_0$.
4. To generate keys for decryption in reverse order directly:
   - For subkey $K_{16}$ (Round 1 of decryption): Apply **0 shifts** to $(C_{16}, D_{16})$.
   - For subsequent subkeys $K_{15}, \dots, K_1$: Apply **right circular shifts** matching the reversed encryption shift schedule:
     - Shift by 1 bit for rounds 2, 9, 16.
     - Shift by 2 bits for rounds 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15.

## Sample Output
```text
Reverse Shift Schedule for Decryption Process:
------------------------------------------------------------
Dec Round | Target Key | Right Shift Amount | Equivalent to
------------------------------------------------------------
    1     |    K16     |         0          | Enc Round 16
    2     |    K15     |         1          | Enc Round 15
    3     |    K14     |         2          | Enc Round 14
...
   16     |    K01     |         1          | Enc Round 01
------------------------------------------------------------
SUCCESS: All 16 decryption subkeys generated in exact reverse order!
```
