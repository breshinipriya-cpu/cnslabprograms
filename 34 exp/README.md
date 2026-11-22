# Experiment 34: Block Cipher Modes Padding Analysis

## Aim
To write a C program to implement bit padding for ECB, CBC, and CFB block cipher modes and explain why an extra padding block is appended even when the final block is already complete.

## Algorithm
1. Start the program.
2. In block cipher modes (ECB, CBC, CFB), plaintext must be partitioned into fixed-size blocks (e.g., 64 bits = 8 bytes).
3. If a message is not an exact multiple of the block size, append a 1-bit followed by 0-bits (byte `0x80` followed by `0x00` bytes).
4. If a message is **already an exact multiple** of the block size, append a full extra padding block of 8 bytes (`80 00 00 00 00 00 00 00`).
5. **Motivation:** This ensures the receiver can remove padding unambiguously without accidentally stripping legitimate trailing data bytes from messages that end with `0x80`.
6. Implement `padBitMethod` and `unpadBitMethod` and verify exact round-trip recovery.
7. Stop.

## Sample Output
```text
Test 1: Message length 7 bytes (Partial Block):
  Padded (8 bytes): 4E 65 74 77 6F 72 6B 80 | 
  Recovered: "Network"

Test 2: Message length 8 bytes (Full Block, Extra Block Appended):
  Padded (16 bytes): 53 65 63 75 72 69 74 79 | 80 00 00 00 00 00 00 00 | 
  Recovered: "Security" (Unambiguous removal!)
```
