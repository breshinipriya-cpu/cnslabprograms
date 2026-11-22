#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Generate monoalphabetic cipher sequence from a keyword
void generateCipherAlphabet(const char *keyword, char cipherAlphabet[]) {
    int used[26] = {0};
    int idx = 0;

    // Add unique keyword letters
    for (int i = 0; keyword[i] != '\0'; i++) {
        if (isalpha(keyword[i])) {
            char ch = toupper(keyword[i]);
            if (!used[ch - 'A']) {
                used[ch - 'A'] = 1;
                cipherAlphabet[idx++] = ch;
            }
        }
    }

    // Add remaining unused alphabet letters in order
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            cipherAlphabet[idx++] = ch;
        }
    }
    cipherAlphabet[26] = '\0';
}

// Encrypt plaintext
void encrypt(const char plaintext[], const char cipherAlphabet[], char ciphertext[]) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];
        if (isupper(ch)) {
            ciphertext[i] = cipherAlphabet[ch - 'A'];
        } else if (islower(ch)) {
            ciphertext[i] = tolower(cipherAlphabet[ch - 'a']);
        } else {
            ciphertext[i] = ch;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

// Decrypt ciphertext
void decrypt(const char ciphertext[], const char cipherAlphabet[], char decrypted[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        char ch = ciphertext[i];
        if (isalpha(ch)) {
            char target = toupper(ch);
            for (int j = 0; j < 26; j++) {
                if (cipherAlphabet[j] == target) {
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
    char keyword[100] = "CIPHER";
    char cipherAlphabet[27];
    char plaintext[256];
    char ciphertext[256];
    char decrypted[256];

    printf("======================================================\n");
    printf("   EXPERIMENT 8: KEYWORD MONOALPHABETIC CIPHER        \n");
    printf("======================================================\n");

    printf("Enter keyword (e.g. CIPHER): ");
    if (fgets(keyword, sizeof(keyword), stdin) != NULL) {
        keyword[strcspn(keyword, "\n")] = '\0';
    }
    if (strlen(keyword) == 0) strcpy(keyword, "CIPHER");

    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("\nGenerated Cipher Mapping:\n");
    printf("plain:  a b c d e f g h i j k l m n o p q r s t u v w x y z\n");
    printf("cipher: ");
    for (int i = 0; i < 26; i++) {
        printf("%c ", cipherAlphabet[i]);
    }
    printf("\n\n");

    printf("Enter plaintext: ");
    if (fgets(plaintext, sizeof(plaintext), stdin) != NULL) {
        plaintext[strcspn(plaintext, "\n")] = '\0';
    }

    encrypt(plaintext, cipherAlphabet, ciphertext);
    printf("Ciphertext:     %s\n", ciphertext);

    decrypt(ciphertext, cipherAlphabet, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
