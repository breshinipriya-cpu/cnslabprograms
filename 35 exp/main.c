#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

// One-Time Pad version of Vigenere Cipher with random numeric key stream
int main() {
    char plaintext[256] = "CRYPTOGRAPHY AND NETWORK SECURITY";
    int keyStream[256];
    char ciphertext[256];
    char decrypted[256];

    printf("======================================================\n");
    printf("   EXPERIMENT 35: ONE-TIME PAD VIGENERE CIPHER        \n");
    printf("======================================================\n\n");

    printf("Enter plaintext (or press Enter for default): ");
    char input[256];
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) > 0) {
            strcpy(plaintext, input);
        }
    }

    int len = strlen(plaintext);
    srand((unsigned int)time(NULL));

    // Generate random key stream between 0 and 25
    for (int i = 0; i < len; i++) {
        keyStream[i] = rand() % 26;
    }

    printf("\nPlaintext:  %s\n", plaintext);
    printf("Key Stream: ");
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            printf("%d ", keyStream[i]);
        } else {
            printf("- ");
        }
    }
    printf("\n\n");

    // OTP Encryption: C_i = (P_i + K_i) mod 26
    for (int i = 0; i < len; i++) {
        char ch = plaintext[i];
        if (isupper(ch)) {
            ciphertext[i] = (ch - 'A' + keyStream[i]) % 26 + 'A';
        } else if (islower(ch)) {
            ciphertext[i] = (ch - 'a' + keyStream[i]) % 26 + 'a';
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[len] = '\0';
    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // OTP Decryption: P_i = (C_i - K_i + 26) mod 26
    for (int i = 0; i < len; i++) {
        char ch = ciphertext[i];
        if (isupper(ch)) {
            decrypted[i] = (ch - 'A' - keyStream[i] + 26) % 26 + 'A';
        } else if (islower(ch)) {
            decrypted[i] = (ch - 'a' - keyStream[i] + 26) % 26 + 'a';
        } else {
            decrypted[i] = ch;
        }
    }
    decrypted[len] = '\0';
    printf("Decrypted Plaintext:  %s\n\n", decrypted);

    if (strcmp(plaintext, decrypted) == 0) {
        printf("VERIFICATION: Decrypted text matches original plaintext!\n");
    }

    return 0;
}
