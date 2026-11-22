# Experiment 18: DES Subkey Disjoint Subset Analysis

## Aim
To write a C program to verify and prove that in the DES key schedule, the first 24 bits of each 48-bit subkey come from the same subset of 28 bits of the initial key, and the second 24 bits come from a disjoint subset of 28 bits of the initial key.

## Algorithm & Proof
1. Start the program.
2. Define Permuted Choice 1 (PC-1) mapping tables for registers $C_0$ (28 bits) and $D_0$ (28 bits).
3. Compute the intersection of $C_0$ and $D_0$ to verify that they are strictly disjoint:
   $$C_0 \cap D_0 = \emptyset$$
4. Define Permuted Choice 2 (PC-2) table (48 bits).
5. Inspect the first 24 indices of PC-2 (indices 0 to 23):
   - Verify every index lies in the range $[1, 28]$, originating exclusively from the $C$ register.
6. Inspect the second 24 indices of PC-2 (indices 24 to 47):
   - Verify every index lies in the range $[29, 56]$, originating exclusively from the $D$ register.
7. Conclude that each subkey's two 24-bit halves are generated from completely disjoint 28-bit key partitions.
8. Stop.

## Sample Output
```text
Checking PC-1 Partition Disjointness:
  Elements in C0: 28 | Elements in D0: 28
  Intersection count (C0 ∩ D0): 0
  Result: C0 and D0 are PROVEN STRICTLY DISJOINT!

Verifying PC-2 Subkey Selection Property:
First 24 bits of subkey (PC-2 entries 1-24):
  All indices <= 28? YES (PROVED) (Bits from C: 24/24, Bits from D: 0/24)

Second 24 bits of subkey (PC-2 entries 25-48):
  All indices > 28?  YES (PROVED) (Bits from D: 24/24, Bits from C: 0/24)
```
