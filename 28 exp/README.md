# Experiment 28: Diffie-Hellman Protocol Analysis

## Aim
To write a C program to analyze the Diffie-Hellman protocol and determine the consequences if participants exchange $x \cdot a \pmod q$ instead of $a^x \pmod q$, and provide the secure method for agreeing on a secret key.

## Questions & Answers
1. **What would happen if participants sent each other $x \cdot a \pmod q$ instead?**
   - The scheme becomes linear and completely insecure.
2. **Can Eve find the secret numbers?**
   - **YES.** Since $a$ and $q$ are public, Eve calculates $a^{-1} \pmod q$ using the Extended Euclidean Algorithm.
   - Eve multiplies Alice's public value by $a^{-1}$:
     $$Y_A \cdot a^{-1} \equiv (x_A \cdot a) \cdot a^{-1} \equiv x_A \pmod q$$
     Both $x_A$ and $x_B$ are recovered instantly.
3. **Can Eve break the system without finding the secret numbers?**
   - **YES.** Even without explicitly isolating $x_A$, any agreed key like $x_A x_B a$ is computed as $Y_A Y_B a^{-1} \pmod q$.
4. **Method for Alice and Bob to agree on a key:**
   - Standard Diffie-Hellman Key Exchange using exponentiation over cyclic group $\mathbb{Z}_q^*$:
     $$Y_A = \alpha^{x_A} \pmod q, \quad Y_B = \alpha^{x_B} \pmod q$$
     $$K = Y_B^{x_A} \equiv Y_A^{x_B} \equiv \alpha^{x_A x_B} \pmod q$$

## Sample Output
```text
--- PART 1: FLAWED LINEAR SCHEME (Sending x * a mod q) ---
Alice chooses secret xA = 45, sends YA = xA * a mod q = 135
Bob chooses secret xB   = 89, sends YB = xB * a mod q = 267

Eve's Attack on Linear Scheme:
  Eve computes modular inverse a^-1 mod q = 118
  Eve extracts Alice's secret xA = 45
  Eve extracts Bob's secret xB   = 89
  Can Eve find the secret numbers? YES! Both xA and xB recovered directly!

--- PART 2: SECURE DIFFIE-HELLMAN KEY EXCHANGE ---
  Alice sends dh_YA = a^xA mod q = 125
  Bob sends dh_YB   = a^xB mod q = 338
  Alice computes Key K = 295
  Bob computes Key K   = 295
  Shared secret matches: YES
```
