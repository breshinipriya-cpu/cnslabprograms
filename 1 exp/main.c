#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using Caesar cipher
void encryptCaesar(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isupper(ch)) {
            text[i] = (ch - 'A' + key) % 26 + 'A';
        } else if (islower(ch)) {
            text[i] = (ch - 'a' + key) % 26 + 'a';
        }
    }
}

// Function to decrypt ciphertext using Caesar cipher
void decryptCaesar(char text[], int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        char ch = text[i];
        if (isupper(ch)) {
            text[i] = (ch - 'A' - key + 26) % 26 + 'A';
        } else if (islower(ch)) {
            text[i] = (ch - 'a' - key + 26) % 26 + 'a';
        }
    }
}

int main() {
    char message[256];
    int key;

    printf("==========================================\n");
    printf("   EXPERIMENT 1: CAESAR CIPHER (1-25)     \n");
    printf("==========================================\n");

    printf("Enter plaintext: ");
    if (fgets(message, sizeof(message), stdin) != NULL) {
        message[strcspn(message, "\n")] = '\0';
    }

    printf("Enter key (1 - 25): ");
    if (scanf("%d", &key) != 1 || key < 1 || key > 25) {
        printf("Invalid key! Key must be between 1 and 25.\n");
        return 1;
    }

    // Encryption
    encryptCaesar(message, key);
    printf("\nCiphertext: %s\n", message);

    // Decryption
    decryptCaesar(message, key);
    printf("Decrypted text: %s\n", message);

    return 0;
}
