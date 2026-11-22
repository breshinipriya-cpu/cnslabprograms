# Experiment 29: SHA-3 Internal State Diffusion Analysis

## Aim
To write a C program to simulate the diffusion of nonzero bits across the SHA-3 (Keccak) internal state matrix with 1024-bit block size (16 rate lanes and 9 zero capacity lanes), and determine how many rounds it takes before all lanes have at least one nonzero bit.

## Theory & Analysis
1. The SHA-3 internal state consists of a $5 \times 5$ matrix of 64-bit lanes (25 lanes = 1600 bits total).
2. With a block size of 1024 bits:
   - Rate $r = 1024$ bits $= 16$ lanes.
   - Capacity $c = 576$ bits $= 9$ lanes.
3. In message block $P_0$, each of the 16 rate lanes has at least one nonzero bit, while the 9 capacity lanes start as all zeros.
4. In Round 1, the **$\theta$ (Theta) step** computes:
   $$C[x] = \bigoplus_{y=0}^{4} A[x, y]$$
   $$D[x] = C[x-1] \oplus \operatorname{ROT}(C[x+1], 1)$$
   $$A'[x, y] = A[x, y] \oplus D[x]$$
5. Because every column has nonzero lanes in $P_0$, every $D[x]$ is nonzero.
6. When $D[x]$ is XORed into each lane $(x, y)$, all 25 lanes (including all zero capacity lanes) receive nonzero bits.
7. **Result:** It takes **exactly 1 round** for all lanes to become nonzero.

## Sample Output
```text
SHA-3 Specification:
- State matrix size: 5 x 5 lanes = 25 lanes (each lane 64 bits = 1600 bits)
- Block size (Rate r): 1024 bits = 16 lanes
- Capacity c:          576 bits  = 9 lanes

Initial State Matrix (Round 0) [1 = Nonzero, 0 = Zero]:
  Row 0: 1 1 1 1 1 
  Row 1: 1 1 1 1 1 
  Row 2: 1 1 1 1 1 
  Row 3: 1 0 0 0 0  <- Contains zero capacity lanes
  Row 4: 0 0 0 0 0  <- Contains zero capacity lanes

State Matrix after Round 1 (Theta step):
  Row 0: 1 1 1 1 1 
  Row 1: 1 1 1 1 1 
  Row 2: 1 1 1 1 1 
  Row 3: 1 1 1 1 1 
  Row 4: 1 1 1 1 1 

CONCLUSION:
Remaining zero lanes after Round 1 = 0
ANSWER: Exactly 1 ROUND!
```
