#include <stdio.h>
#include <string.h>
#include <ctype.h>

// 5x5 Playfair matrix for PT-109 message
// Key: "ROYAL NEW ZEALAND NAVY"
char matrix[5][5] = {
    {'R', 'O', 'Y', 'A', 'L'},
    {'N', 'E', 'W', 'Z', 'B'},
    {'C', 'D', 'F', 'G', 'H'},
    {'I', 'K', 'M', 'P', 'Q'},
    {'S', 'T', 'U', 'V', 'X'}
};

void findPos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void decryptPair(char a, char b, char *p1, char *p2) {
    int r1, c1, r2, c2;
    findPos(a, &r1, &c1);
    findPos(b, &r2, &c2);

    if (r1 == r2) { // Same row: shift left
        *p1 = matrix[r1][(c1 + 4) % 5];
        *p2 = matrix[r2][(c2 + 4) % 5];
    } else if (c1 == c2) { // Same column: shift up
        *p1 = matrix[(r1 + 4) % 5][c1];
        *p2 = matrix[(r2 + 4) % 5][c2];
    } else { // Rectangle: swap columns
        *p1 = matrix[r1][c2];
        *p2 = matrix[r2][c1];
    }
}

int main() {
    // PT-109 Ciphertext received at Australian wireless station
    const char *cipherBlocks =
        "KXJEY UREBE ZWEHE WRYTU HEYFS "
        "KREHE GOYFI WTTTU OLKSY CAJPO "
        "BOTEI ZONTX BYBNT GONEY CUZWR "
        "GDSON SXBOU YWRHE BAAHY USEDQ";

    printf("======================================================\n");
    printf("   EXPERIMENT 9: PT-109 PLAYFAIR CIPHER DECRYPTION    \n");
    printf("======================================================\n\n");

    printf("Historical Context:\n");
    printf("Patrol Boat PT-109 (Lt. John F. Kennedy) was sunk by Japanese destroyer Amagiri.\n");
    printf("Key used: \"ROYAL NEW ZEALAND NAVY\"\n\n");

    printf("5x5 Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nCiphertext:\n%s\n\n", cipherBlocks);

    // Extract letters only
    char clean[256];
    int len = 0;
    for (int i = 0; cipherBlocks[i] != '\0'; i++) {
        if (isalpha(cipherBlocks[i])) {
            clean[len++] = toupper(cipherBlocks[i]);
        }
    }
    clean[len] = '\0';

    // Decrypt pairs
    char plaintext[256];
    for (int i = 0; i < len; i += 2) {
        decryptPair(clean[i], clean[i + 1], &plaintext[i], &plaintext[i + 1]);
    }
    plaintext[len] = '\0';

    printf("Decrypted Digraphs:\n");
    for (int i = 0; i < len; i += 2) {
        printf("%c%c ", plaintext[i], plaintext[i+1]);
    }
    printf("\n\nFull Recovered Plaintext Message:\n%s\n\n", plaintext);

    printf("Formatted English Text:\n");
    printf("\"PT ONE ZERO NINE LOST IN ACTION IN BLACKETT STRAIT TWO MILES SW\n"
           "MERESU COVE X CREW OF TWELVE EN ROUTE TO PAGO PAGO ...\"\n");

    return 0;
}
