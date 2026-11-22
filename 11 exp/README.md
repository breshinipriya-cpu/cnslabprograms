# Experiment 11: Playfair Cipher Keyspace Analysis

## Aim
To write a C program to calculate the total number of possible keys in the Playfair cipher as an approximate power of 2, and determine the number of effectively unique keys when equivalent encryption results are taken into account.

## Mathematical Derivation
1. **Total Theoretical Keys:**
   - A Playfair cipher key matrix contains 25 distinct letters.
   - The number of arrangements is $25!$:
     $$25! \approx 1.5511 \times 10^{25}$$
   - In powers of 2:
     $$\log_2(25!) = \sum_{i=1}^{25} \log_2(i) \approx 83.68 \approx 2^{84}$$
2. **Effectively Unique Keys:**
   - Shifting all rows cyclically (5 choices) or all columns cyclically (5 choices) results in identical encryption behavior.
   - Symmetries = $5 \times 5 = 25$.
   - Unique keys = $\frac{25!}{25} = 24!$:
     $$24! \approx 6.2045 \times 10^{23} \approx 2^{79.04} \approx 2^{79}$$
   - Further accounting for planar reflections gives $\frac{24!}{4} \approx 2^{77}$.

## Sample Output
```text
PART 1: Total possible keys (ignoring identical encryption results):
  Formula: 25!
  Scientific notation: 1.5511e+25
  Power of 2: 2^(83.68) ≈ 2^84

PART (a): Effectively unique keys (accounting for equivalent keys):
  - Total cyclic symmetries = 5 * 5 = 25 equivalent matrices per key.
  Formula: 25! / 25 = 24!
  24! = 6.2045e+23
  Power of 2: 2^(79.04) ≈ 2^79
```
