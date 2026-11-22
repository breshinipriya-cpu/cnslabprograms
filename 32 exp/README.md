# Experiment 32: DSA Signature and Nonce Implication Analysis

## Aim
To write a C program to demonstrate that DSA generates distinct signatures for the same message due to per-signature nonce $k$ (unlike deterministic RSA), and analyze the catastrophic implication if nonce $k$ is reused.

## Theory & Analysis
1. **Deterministic vs. Randomized Signatures:**
   - **RSA:** $S = M^d \pmod n$. Deterministic; signing the same message always produces the exact same signature.
   - **DSA:** Uses random ephemeral value $k$:
     $$r = (g^k \pmod p) \pmod q, \quad s = k^{-1}(H(M) + xr) \pmod q$$
     Every signature on the same message is unique.
2. **Catastrophic Implication of Nonce Reuse:**
   - If a signer reuses nonce $k$ across two messages $M_1$ and $M_2$:
     $$s_1 - s_2 = k^{-1}(H(M_1) - H(M_2)) \pmod q$$
     $$k = (H(M_1) - H(M_2)) \cdot (s_1 - s_2)^{-1} \pmod q$$
   - Once $k$ is extracted, private key $x$ is revealed immediately:
     $$x = r^{-1}(s_1 k - H(M_1)) \pmod q$$
   - An attacker extracts the private signing key with simple modular arithmetic!

## Sample Output
```text
Demonstrating Signature Variation on SAME Message M = 19:
  Signature 1 (with k=15): (r = 17, s = 25)
  Signature 2 (with k=22): (r = 43, s = 31)
  Result: Signatures are completely different!

CRITICAL IMPLICATION: THE REUSED NONCE (k) DISASTER
  Message 1: M1 = 19 -> Sig1: (r = 17, s = 25)
  Message 2: M2 = 33 -> Sig2: (r = 17, s = 20)
  Notice that r1 == r2 (17 == 17) because k was reused!

Adversary Attack:
  Cracked Nonce k = 15 (Actual k = 15)
  CRACKED PRIVATE KEY x = 24 (Actual x = 24)

CONCLUSION:
  Reusing nonce k even ONCE completely reveals the private key x!
```
