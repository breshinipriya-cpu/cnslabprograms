# Cryptography and Network Security (CNS) Laboratory

**Programming Language:** C  
**Course:** Cryptography and Network Security Lab  
**Specification:** Complete implementation of 40 laboratory experiments in C based on the university curriculum ("CNS LIST OF PROGRAMS").

---

## Overview

This repository contains clean, modular, and fully tested C implementations of 40 Cryptography and Network Security experiments. Each experiment is organized inside its own directory with complete source code (`main.c`) and detailed documentation (`README.md`) specifying the aim, mathematical theory/algorithm, sample input, and sample output.

---

## List of Experiments

| Exp No. | Experiment Title | Description |
|:-------:|:-----------------|:------------|
| [1 exp](./1%20exp) | Caesar Cipher | Implementation of Caesar Cipher substitution for shifts $k \in [1, 25]$. |
| [2 exp](./2%20exp) | Monoalphabetic Substitution Cipher | Plaintext to ciphertext mapping where each letter maps to a unique ciphertext letter. |
| [3 exp](./3%20exp) | Playfair Cipher | Digraph substitution using a $5 \times 5$ matrix generated from a keyword. |
| [4 exp](./4%20exp) | Polyalphabetic Substitution (Vigenère) | Successive monoalphabetic substitution depending on a repeated keyword. |
| [5 exp](./5%20exp) | Affine Caesar Cipher Analysis | Mathematical limitations on $b$ and determining allowed/disallowed values of $a$. |
| [6 exp](./6%20exp) | Breaking an Affine Cipher | Cryptanalysis given most frequent letters 'B' and 'U' via modular linear systems. |
| [7 exp](./7%20exp) | Substitution Cryptanalysis (The Gold-Bug) | Frequency analysis and decryption of Edgar Allan Poe's classic cipher. |
| [8 exp](./8%20exp) | Keyword-Based Monoalphabetic Cipher | Generating a cipher sequence from a keyword followed by unused letters. |
| [9 exp](./9%20exp) | PT-109 Playfair Cipher Decryption | Decryption of John F. Kennedy's historic WWII naval patrol boat message. |
| [10 exp](./10%20exp) | Playfair Cipher with Given Matrix | Encryption of Cadogan West message using a custom $5 \times 5$ matrix. |
| [11 exp](./11%20exp) | Playfair Cipher Keyspace Analysis | Expressing total keys ($25! \approx 2^{84}$) and unique keys ($24! \approx 2^{79}$) as powers of 2. |
| [12 exp](./12%20exp) | 2x2 Hill Cipher Encryption & Decryption | Matrix multiplication modulo 26 using key matrix $[[9, 4], [5, 7]]$. |
| [13 exp](./13%20exp) | Known & Chosen Plaintext Attack on Hill Cipher | Recovering secret $2 \times 2$ key matrix via matrix inversion and identity probes. |
| [14 exp](./14%20exp) | One-Time Pad Vigenère Cipher | Stream shift encryption and deriving key streams for arbitrary target decryptions. |
| [15 exp](./15%20exp) | Letter Frequency Attack on Additive Cipher | Automated cryptanalysis ranking top 10 candidate plaintexts using frequency scoring. |
| [16 exp](./16%20exp) | Frequency Attack on Monoalphabetic Substitution | Automated cryptanalysis of substitution ciphers ranking top 10 plaintexts. |
| [17 exp](./17%20exp) | DES Decryption Key Schedule Design | Designing the right-shift key schedule to generate subkeys $K_{16} \dots K_1$ in reverse. |
| [18 exp](./18%20exp) | DES Subkey Disjoint Subset Proof | Verifying that subkey halves (bits 1–24 and 25–48) derive from disjoint 28-bit key partitions. |
| [19 exp](./19%20exp) | 3DES in CBC Mode | Implementation of Triple-DES in CBC mode; evaluating security vs performance trade-offs. |
| [20 exp](./20%20exp) | Error Propagation in ECB vs CBC Modes | Analyzing error bounds from ciphertext transmission faults vs source plaintext errors. |
| [21 exp](./21%20exp) | Block Cipher Padding Motivation | Implementing bit padding (`0x80` then `0x00`) and justifying full dummy pad blocks. |
| [22 exp](./22%20exp) | S-DES in Cipher Block Chaining (CBC) Mode | Full Simplified DES in CBC mode verified against standard binary test vectors. |
| [23 exp](./23%20exp) | S-DES in Counter (CTR) Mode | Simplified DES in CTR mode verified against standard binary test vectors. |
| [24 exp](./24%20exp) | RSA Private Key Calculation | Factoring $n = 3599$ into $59 \times 61$ and computing private key $d$ for $e = 31$. |
| [25 exp](./25%20exp) | RSA Common Factor Vulnerability | Proving that plaintext sharing a factor with $n$ allows instant factoring via $\gcd(C, n)$. |
| [26 exp](./26%20exp) | RSA Modulus Reuse Security Analysis | Proving that generating new $(e, d)$ with a compromised modulus $n$ is completely unsafe. |
| [27 exp](./27%20exp) | Attack on Character-by-Character RSA | Codebook/dictionary attack cracking unpadded small-domain RSA in $O(1)$ time. |
| [28 exp](./28%20exp) | Diffie-Hellman vs Linear Protocol Analysis | Demonstrating modular inverse attack on linear key exchange vs secure DH exponentiation. |
| [29 exp](./29%20exp) | SHA-3 Internal State Diffusion Analysis | Proving all 25 lanes become nonzero in 1 round via $\theta$ step column parity. |
| [30 exp](./30%20exp) | CBC-MAC One-Block Forgery Attack | Forging valid MAC for $X \parallel (X \oplus T)$ without knowledge of secret key $K$. |
| [31 exp](./31%20exp) | CMAC Subkey Generation (64 & 128 Bits) | Deriving $K_1, K_2$ with constants `0x1B` and `0x87` via left shift and conditional XOR. |
| [32 exp](./32%20exp) | DSA Nonce Variation & Reuse Vulnerability | Analyzing signature randomization and proving private key $x$ extraction on nonce reuse. |
| [33 exp](./33%20exp) | Full Data Encryption Standard (DES) | Complete 16-round 64-bit DES block cipher implementation with 56-bit key schedule. |
| [34 exp](./34%20exp) | Block Cipher Modes Padding (ECB, CBC, CFB) | Bit-level padding implementation and unambiguous stripping analysis. |
| [35 exp](./35%20exp) | One-Time Pad Vigenère with Random Stream | Symmetric stream cipher using random shifts in $[0, 25]$ with perfect secrecy properties. |
| [36 exp](./36%20exp) | Affine Caesar Cipher One-to-One Verification | Testing injectivity, identifying collisions for $\gcd(a, 26) \ne 1$, and modular inversion. |
| [37 exp](./37%20exp) | Frequency Attack on Monoalphabetic Substitution | Automated ranking of top 10 likely plaintexts using frequency-based candidate permutations. |
| [38 exp](./38%20exp) | Known and Chosen Plaintext Attacks on Hill Cipher | Key recovery via matrix inversion $K = P^{-1} \cdot C \pmod{26}$ and identity probes. |
| [39 exp](./39%20exp) | Automated Frequency Attack on Additive Cipher | Exhaustive shift search and English correlation scoring producing top 10 candidates. |
| [40 exp](./40%20exp) | Frequency Cryptanalysis of Substitution Cipher | Automated frequency analysis and permutation ranking producing top 10 plaintexts. |

---

## Compilation and Execution

Every experiment can be compiled with GCC:

```bash
# Example: Compiling and running Experiment 1
cd "1 exp"
gcc main.c -o main.exe
./main.exe
```

For mathematical programs requiring the math library (e.g. Exp 11, Exp 24):
```bash
gcc main.c -o main.exe -lm
./main.exe
```

---

## Repository Structure

```text
cnslabprograms/
├── CNS LIST OF PROGRAMS  (3).pdf
├── README.md
├── 1 exp/
│   ├── main.c
│   └── README.md
├── 2 exp/
│   ├── main.c
│   └── README.md
...
└── 40 exp/
    ├── main.c
    └── README.md
```
