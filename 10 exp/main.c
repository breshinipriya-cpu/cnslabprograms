#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Specified 5x5 Playfair matrix from question:
// M F H I/J K
// U N O P   Q
// Z V W X   Y
// E L A R   G
// D S T B   C
char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
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

// Prepare digraphs
int prepareText(const char *in, char *out) {
    char temp[512];
    int tlen = 0;
    for (int i = 0; in[i] != '\0'; i++) {
        if (isalpha(in[i])) {
            char ch = toupper(in[i]);
            if (ch == 'J') ch = 'I';
            temp[tlen++] = ch;
        }
    }

    int outLen = 0;
    for (int i = 0; i < tlen; i++) {
        out[outLen++] = temp[i];
        if (i + 1 < tlen && temp[i] == temp[i + 1] && (outLen % 2 != 0)) {
            out[outLen++] = 'X';
        }
    }
    if (outLen % 2 != 0) {
        out[outLen++] = 'X'; // Pad with X
    }
    out[outLen] = '\0';
    return outLen;
}

// Encrypt Playfair
void encryptPlayfair(char text[], int len) {
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPos(text[i], &r1, &c1);
        findPos(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            text[i] = matrix[r1][(c1 + 1) % 5];
            text[i + 1] = matrix[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            text[i] = matrix[(r1 + 1) % 5][c1];
            text[i + 1] = matrix[(r2 + 1) % 5][c2];
        } else {
            text[i] = matrix[r1][c2];
            text[i + 1] = matrix[r2][c1];
        }
    }
}

int main() {
    const char *message = "Must see you over Cadogan West. Coming at once.";
    char formatted[512];

    printf("======================================================\n");
    printf("   EXPERIMENT 10: PLAYFAIR CIPHER (GIVEN MATRIX)      \n");
    printf("======================================================\n\n");

    printf("Given Playfair Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nOriginal Message: %s\n", message);

    int len = prepareText(message, formatted);
    printf("Formatted Digraphs: %s\n", formatted);

    encryptPlayfair(formatted, len);
    printf("\nCiphertext: ");
    for (int i = 0; i < len; i += 2) {
        printf("%c%c ", formatted[i], formatted[i + 1]);
    }
    printf("\nConcatenated Ciphertext: %s\n", formatted);

    return 0;
}
