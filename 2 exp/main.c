#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using Monoalphabetic substitution
void encryptMono(const char plaintext[], const char key[], char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isupper(ch)) {
            ciphertext[i] = toupper(key[ch - 'A']);
        } else if (islower(ch)) {
            ciphertext[i] = tolower(key[ch - 'a']);
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Function to decrypt ciphertext using Monoalphabetic substitution
void decryptMono(const char ciphertext[], const char key[], char decrypted[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char target = toupper(ch);
            for (int j = 0; j < 26; j++) {
                if (toupper(key[j]) == target) {
                    decrypted[i] = isupper(ch) ? ('A' + j) : ('a' + j);
                    break;
                }
            }
        } else {
            decrypted[i] = ch;
        }
    }
    decrypted[strlen(ciphertext)] = '\0';
}

int main() {
    char plaintext[256];
    char ciphertext[256];
    char decrypted[256];
    // Default 26-character unique substitution key
    char key[27] = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("===================================================\n");
    printf("   EXPERIMENT 2: MONOALPHABETIC SUBSTITUTION CIPHER\n");
    printf("===================================================\n");
    printf("Alphabet: abcdefghijklmnopqrstuvwxyz\n");
    printf("Key:      %s\n\n", key);

    printf("Enter plaintext: ");
    if (fgets(plaintext, sizeof(plaintext), stdin) != NULL) {
        plaintext[strcspn(plaintext, "\n")] = '\0';
    }

    encryptMono(plaintext, key, ciphertext);
    printf("\nCiphertext:     %s\n", ciphertext);

    decryptMono(ciphertext, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
