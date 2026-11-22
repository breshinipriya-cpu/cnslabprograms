#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

// Prepare 5x5 Playfair matrix from key
void generateMatrix(const char *key) {
    int map[26] = {0};
    map['J' - 'A'] = 1; // 'I' and 'J' share a position
    int r = 0, c = 0;

    // Place key characters
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !map[ch - 'A']) {
            map[ch - 'A'] = 1;
            matrix[r][c++] = ch;
            if (c == 5) { r++; c = 0; }
        }
    }

    // Place remaining alphabet characters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!map[ch - 'A']) {
            map[ch - 'A'] = 1;
            matrix[r][c++] = ch;
            if (c == 5) { r++; c = 0; }
        }
    }
}

// Find row and column of character
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I';
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (matrix[r][c] == ch) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

// Prepare plaintext into digraphs
int prepareText(const char *in, char *out) {
    int len = 0;
    for (int i = 0; in[i] != '\0'; i++) {
        if (isalpha(in[i])) {
            char ch = toupper(in[i]);
            if (ch == 'J') ch = 'I';
            out[len++] = ch;
        }
    }

    // Insert 'X' between identical letters in same pair
    char formatted[512];
    int flen = 0;
    for (int i = 0; i < len; i++) {
        formatted[flen++] = out[i];
        if (i + 1 < len && out[i] == out[i + 1] && (flen % 2 != 0)) {
            formatted[flen++] = 'X';
        }
    }
    if (flen % 2 != 0) {
        formatted[flen++] = 'X'; // Pad if odd length
    }
    formatted[flen] = '\0';
    strcpy(out, formatted);
    return flen;
}

// Encrypt digraphs
void encryptPlayfair(char text[], int len) {
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) { // Same row
            text[i] = matrix[r1][(c1 + 1) % 5];
            text[i + 1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) { // Same column
            text[i] = matrix[(r1 + 1) % 5][c1];
            text[i + 1] = matrix[(r2 + 1) % 5][c2];
        } else { // Rectangle
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

// Decrypt digraphs
void decryptPlayfair(char text[], int len) {
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        if (r1 == r2) { // Same row
            text[i] = matrix[r1][(c1 + 4) % 5];
            text[i + 1] = matrix[r2][(c2 + 4) % 5];
        } else if (c1 == c2) { // Same column
            text[i] = matrix[(r1 + 4) % 5][c1];
            text[i + 1] = matrix[(r2 + 4) % 5][c2];
        } else { // Rectangle
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

int main() {
    char key[100];
    char text[512];

    printf("==========================================\n");
    printf("   EXPERIMENT 3: PLAYFAIR CIPHER (5x5)    \n");
    printf("==========================================\n");

    printf("Enter keyword: ");
    if (fgets(key, sizeof(key), stdin) != NULL) {
        key[strcspn(key, "\n")] = '\0';
    }

    generateMatrix(key);

    printf("\n5x5 Playfair Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nEnter plaintext: ");
    if (fgets(text, sizeof(text), stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    }

    int len = prepareText(text, text);
    printf("Formatted Text: %s\n", text);

    encryptPlayfair(text, len);
    printf("Ciphertext:     %s\n", text);

    decryptPlayfair(text, len);
    printf("Decrypted text: %s\n", text);

    return 0;
}
