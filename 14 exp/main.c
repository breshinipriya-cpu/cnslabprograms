#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 14: ONE-TIME PAD VIGENERE CIPHER        \n");
    printf("======================================================\n\n");

    // Plaintext: "send more money"
    const char *text1 = "sendmoremoney";
    int keyStream1[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int len1 = strlen(text1);

    printf("--- PART (a): Encryption of 'send more money' ---\n");
    printf("Plaintext:  %s\n", text1);
    printf("Key stream: ");
    for (int i = 0; i < len1; i++) printf("%d ", keyStream1[i]);
    printf("\n");

    char cipher1[32];
    for (int i = 0; i < len1; i++) {
        int p = text1[i] - 'a';
        int c = (p + keyStream1[i]) % 26;
        cipher1[i] = c + 'a';
    }
    cipher1[len1] = '\0';
    printf("Ciphertext: %s\n\n", cipher1);

    // Part (b): Using the ciphertext produced in part (a), find a key
    // so that it decrypts to "cash not needed"
    const char *text2 = "cashnotneeded";
    int len2 = strlen(text2);
    int keyStream2[32];

    printf("--- PART (b): Finding Key for 'cash not needed' ---\n");
    printf("Desired Plaintext: %s\n", text2);
    printf("Equation: (C - K') mod 26 = P2  ==>  K' = (C - P2) mod 26\n");

    printf("Calculated Key Stream:\n");
    for (int i = 0; i < len2; i++) {
        int c = cipher1[i] - 'a';
        int p2 = text2[i] - 'a';
        int k_prime = (c - p2) % 26;
        if (k_prime < 0) k_prime += 26;
        keyStream2[i] = k_prime;
        printf("K[%2d] = (%2d - %2d) mod 26 = %2d\n", i, c, p2, k_prime);
    }

    printf("\nRequired Key Stream Stream: ");
    for (int i = 0; i < len2; i++) printf("%d ", keyStream2[i]);
    printf("\n\n");

    // Verification of decryption with newly discovered key
    char verifiedPlain[32];
    for (int i = 0; i < len2; i++) {
        int c = cipher1[i] - 'a';
        int p = (c - keyStream2[i] + 26) % 26;
        verifiedPlain[i] = p + 'a';
    }
    verifiedPlain[len2] = '\0';

    printf("Verification Decryption with Key 2:\n");
    printf("Decrypted text: %s\n", verifiedPlain);
    printf("Result matches target plaintext perfectly! (Demonstrates Shannon's OTP property)\n");

    return 0;
}
