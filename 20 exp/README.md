# Experiment 20: Error Propagation in ECB and CBC Modes

## Aim
To write a C program to analyze and demonstrate error propagation in Cipher Block Chaining (CBC) mode:
- a. Determine if transmission errors in $C_1$ affect blocks beyond $P_2$.
- b. Determine how a source bit error in $P_1$ propagates across ciphertext blocks and its effect at the receiver.

## Analysis & Answers
1. **Transmission Error in $C_1$ (Part a):**
   - Receiver equations:
     $$P_1 = D_K(C_1) \oplus IV$$
     $$P_2 = D_K(C_2) \oplus C_1$$
     $$P_3 = D_K(C_3) \oplus C_2$$
   - A bit error in $C_1$ corrupts $P_1$ completely (through $D_K$) and corrupts $P_2$ at the exact bit position where $C_1$ was flipped.
   - For $i \ge 3$, $P_i$ depends on $C_i$ and $C_{i-1}$, which are intact.
   - **Answer:** **No blocks beyond $P_2$ are affected.** CBC is self-synchronizing.
2. **Source Plaintext Error in $P_1$ (Part b):**
   - Sender equations:
     $$C_1 = E_K(P_1 \oplus IV)$$
     $$C_2 = E_K(P_2 \oplus C_1)$$
   - Since $C_1$ changes, every subsequent ciphertext block $C_2, C_3, \dots, C_N$ also changes.
   - **Answer:** The error propagates through **all subsequent ciphertext blocks**. At the receiver, every block decrypts properly according to the sender's ciphertext, so only $P_1$ carries the original source bit error.

## Sample Output
```text
--- PART (a): TRANSMISSION ERROR IN CIPHERTEXT C1 ---
Decrypted Plaintext at Receiver:
  P1: 0x1111111111111110 -> CORRUPTED
  P2: 0x2222222222222223 -> CORRUPTED
  P3: 0x3333333333333333 -> CORRECT
  P4: 0x4444444444444444 -> CORRECT

--- PART (b): SOURCE PLAINTEXT ERROR IN P1 ---
Ciphertext Propagation:
  C1 changed? YES (PROPAGATED)
  C2 changed? YES (PROPAGATED)
  C3 changed? YES (PROPAGATED)
  C4 changed? YES (PROPAGATED)
```
