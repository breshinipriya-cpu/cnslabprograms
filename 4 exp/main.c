#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Encrypt plaintext using Polyalphabetic (Vigenere) cipher
void encryptVigenere(const char plaintext[], const char key[], char ciphertext[]) {
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; plaintext[i] != '\0'; i++) {
        char p = plaintext[i];
        if (isupper(p)) {
            char k = toupper(key[j % keyLen]) - 'A';
            ciphertext[i] = (p - 'A' + k) % 26 + 'A';
            j++;
        } else if (islower(p)) {
            char k = tolower(key[j % keyLen]) - 'a';
            ciphertext[i] = (p - 'a' + k) % 26 + 'a';
            j++;
        } else {
            ciphertext[i] = p;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Decrypt ciphertext using Polyalphabetic (Vigenere) cipher
void decryptVigenere(const char ciphertext[], const char key[], char decrypted[]) {
    int keyLen = strlen(key);
    int j = 0;

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (isupper(c)) {
            char k = toupper(key[j % keyLen]) - 'A';
            decrypted[i] = (c - 'A' - k + 26) % 26 + 'A';
            j++;
        } else if (islower(c)) {
            char k = tolower(key[j % keyLen]) - 'a';
            decrypted[i] = (c - 'a' - k + 26) % 26 + 'a';
            j++;
        } else {
            decrypted[i] = c;
        }
    }
    decrypted[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[256];
    char key[100];
    char ciphertext[256];
    char decrypted[256];

    printf("======================================================\n");
    printf("   EXPERIMENT 4: POLYALPHABETIC CIPHER (VIGENERE)    \n");
    printf("======================================================\n");

    printf("Enter plaintext: ");
    if (fgets(plaintext, sizeof(plaintext), stdin) != NULL) {
        plaintext[strcspn(plaintext, "\n")] = '\0';
    }

    printf("Enter key: ");
    if (fgets(key, sizeof(key), stdin) != NULL) {
        key[strcspn(key, "\n")] = '\0';
    }

    encryptVigenere(plaintext, key, ciphertext);
    printf("\nCiphertext:     %s\n", ciphertext);

    decryptVigenere(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
