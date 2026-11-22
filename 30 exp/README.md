# Experiment 30: CBC-MAC Forgery Attack

## Aim
To write a C program to demonstrate the classic CBC-MAC forgery attack where given a one-block message $X$ and its MAC tag $T = \operatorname{MAC}(K, X)$, an adversary can forge the MAC for the two-block message $X \parallel (X \oplus T)$ without knowing key $K$.

## Mathematical Proof
1. In CBC-MAC with $IV = 0$:
   - For a single block message $X$:
     $$T = E_K(X)$$
2. Construct two-block message $M' = X_1 \parallel X_2$ where $X_1 = X$ and $X_2 = X \oplus T$:
   - **Round 1:**
     $$C_1 = E_K(X_1 \oplus 0) = E_K(X) = T$$
   - **Round 2:**
     $$C_2 = E_K(X_2 \oplus C_1) = E_K((X \oplus T) \oplus T) = E_K(X) = T$$
3. Therefore:
   $$\operatorname{MAC}(K, X \parallel (X \oplus T)) = T$$
4. The adversary produces a valid MAC $T$ for the longer message $X \parallel (X \oplus T)$ without knowledge of the secret key $K$.

## Sample Output
```text
1. Legitimate One-Block Message:
   X = 0x4142434445464748
   Tag T = MAC(K, X) = 0x56DE2BB095DA2664

2. Adversary Constructs Forged Two-Block Message:
   Block 1: X         = 0x4142434445464748
   Block 2: X XOR T   = 0x179C68F4D09C612C

3. Verification of Forged Tag:
   MAC(K, X || (X XOR T)) = 0x56DE2BB095DA2664
   Original Tag T         = 0x56DE2BB095DA2664

RESULT: FORGERY ATTACK SUCCESSFUL!
The adversary successfully forged a valid MAC for a 2-block message without possessing the secret key K!
```
