# Experiment 31: CMAC Subkey Generation

## Aim
To write a C program to implement subkey generation in Cipher-based Message Authentication Code (CMAC) for 64-bit and 128-bit blocks, identify the reduction constants, and explain how the left shift and XOR achieve field multiplication.

## Theory & Questions
1. **CMAC Subkey Generation Process:**
   - Compute $L = \operatorname{CIPH}_K(0^b)$.
   - If $\operatorname{MSB}_1(L) == 0$, $K_1 = L \ll 1$; else $K_1 = (L \ll 1) \oplus \text{Const}_b$.
   - If $\operatorname{MSB}_1(K_1) == 0$, $K_2 = K_1 \ll 1$; else $K_2 = (K_1 \ll 1) \oplus \text{Const}_b$.
2. **What constants are needed?**
   - **64-bit block size:** Constant $R_{64} = \text{0x1B}$ (based on irreducible polynomial $x^{64} + x^4 + x^3 + x + 1$).
   - **128-bit block size:** Constant $R_{128} = \text{0x87}$ (based on irreducible polynomial $x^{128} + x^7 + x^2 + x + 1$).
3. **How left shift and XOR accomplishes the desired result:**
   - Left shifting represents polynomial multiplication by $x$ in $\text{GF}(2^b)$.
   - When the high bit is 1, multiplication results in an overflow coefficient of $x^b$.
   - XORing with $R_b$ subtracts (adds in characteristic 2) the field polynomial, accomplishing modular polynomial reduction.

## Sample Output
```text
QUESTIONS ANSWERED:
a. What constants are needed for block sizes of 64 and 128 bits?
   - For 64-bit blocks:  Constant Rb = 0x1B
   - For 128-bit blocks: Constant Rb = 0x87

--- 1. 64-Bit Subkey Derivation Demo ---
  L  = 0x48656C6C6F20576F (MSB = 0)
  K1 = 0x90CAD8D8DE40AEDE
  K2 = 0x2195B1B1BC815D87

--- 2. 128-Bit Subkey Derivation Demo ---
  L  = 0x80000000000000000000000000000001 (MSB = 1 -> triggers XOR)
  K1 = 0x00000000000000000000000000000085
  K2 = 0x0000000000000000000000000000010A
```
