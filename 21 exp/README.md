# Experiment 21: Block Cipher Padding Motivation

## Aim
To write a C program to implement block cipher padding (one 1-bit followed by zero bits) for ECB, CBC, and CFB modes, and explain the motivation for appending a padding block even when the plaintext block is already complete.

## Algorithm & Theoretical Motivation
1. Start the program.
2. In block ciphers, the receiver must be able to remove padding bytes unambiguously:
   - If an unpadded message naturally ends with bits that resemble padding (e.g. `1000...`), an unpadding algorithm would erroneously remove actual plaintext.
   - To prevent ambiguity, the sender pads **every** message:
     - If plaintext length is not a multiple of the block size, append a 1 bit followed by zeros to complete the block.
     - If plaintext length is an exact multiple of the block size, append a full extra padding block (e.g. `0x80` followed by `0x00`s).
3. Implement `padMessage()` and `unpadMessage()`.
4. Demonstrate padding on:
   - Case 1: Incomplete block (5 bytes).
   - Case 2: Complete block (8 bytes) resulting in an extra padding block.
5. Verify both messages are recovered with 100% integrity.
6. Stop.

## Sample Output
```text
MOTIVATION QUESTION:
"What is the motivation for including a padding block when padding is not needed?"

ANSWER:
- By ALWAYS adding padding (even a full dummy block of 8 bytes when already aligned),
  the receiver is guaranteed that every message ends with valid padding bytes
  and can be stripped safely and unambiguously without data loss.

CASE 1: Message length = 5 bytes (Non-multiple of 8)
  Original message: "Hello"
  Padded hex (8 bytes):  48 65 6C 6C 6F 80 00 00 | 
  Unpadded text: "Hello" (Length: 5)

CASE 2: Message length = 8 bytes (Exact multiple of 8)
  Original message: "Security"
  Padded hex (16 bytes):  53 65 63 75 72 69 74 79 | 80 00 00 00 00 00 00 00 | 
  Unpadded text: "Security" (Length: 8) -> Recovered exactly!
```
