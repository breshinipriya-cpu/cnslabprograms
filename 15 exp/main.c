#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Standard English letter frequencies (A-Z) in percentages
const double englishFreq[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75,  7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15,  1.97, 0.07
};

typedef struct {
    int key;
    double score;
    char plaintext[512];
} Candidate;

// Compare candidate scores for sorting descending
int compareCandidates(const void *a, const void *b) {
    Candidate *c1 = (Candidate *)a;
    Candidate *c2 = (Candidate *)b;
    if (c2->score > c1->score) return 1;
    if (c2->score < c1->score) return -1;
    return 0;
}

int main() {
    char ciphertext[512] = "KHOOR ZRUOG WKLV LV DQ DGGLWLYH FLSKHU WHVW PHVVDJH";
    Candidate candidates[26];
    int topN = 10;

    printf("======================================================\n");
    printf("   EXPERIMENT 15: LETTER FREQUENCY ATTACK ON          \n");
    printf("                 ADDITIVE CIPHER                      \n");
    printf("======================================================\n\n");

    printf("Ciphertext: %s\n\n", ciphertext);
    printf("Default top plaintexts requested: %d\n\n", topN);

    int textLen = strlen(ciphertext);

    // Test all 26 possible shift keys
    for (int key = 0; key < 26; key++) {
        candidates[key].key = key;
        double score = 0.0;
        int count[26] = {0};
        int alphaCount = 0;

        // Decrypt with shift 'key'
        for (int i = 0; i < textLen; i++) {
            char ch = ciphertext[i];
            if (isupper(ch)) {
                char dec = (ch - 'A' - key + 26) % 26 + 'A';
                candidates[key].plaintext[i] = dec;
                count[dec - 'A']++;
                alphaCount++;
            } else if (islower(ch)) {
                char dec = (ch - 'a' - key + 26) % 26 + 'a';
                candidates[key].plaintext[i] = dec;
                count[dec - 'a']++;
                alphaCount++;
            } else {
                candidates[key].plaintext[i] = ch;
            }
        }
        candidates[key].plaintext[textLen] = '\0';

        // Calculate frequency correlation score
        if (alphaCount > 0) {
            for (int i = 0; i < 26; i++) {
                double observed = ((double)count[i] / alphaCount) * 100.0;
                score += observed * englishFreq[i];
            }
        }
        candidates[key].score = score;
    }

    // Sort candidates descending by likelihood score
    qsort(candidates, 26, sizeof(Candidate), compareCandidates);

    printf("Top %d Most Likely Plaintexts:\n", topN);
    printf("--------------------------------------------------------------------------------\n");
    printf("Rank | Key | Score   | Decrypted Text Preview\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < topN && i < 26; i++) {
        printf("%4d | %3d | %7.2f | %s\n", 
               i + 1, candidates[i].key, candidates[i].score, candidates[i].plaintext);
    }
    printf("--------------------------------------------------------------------------------\n");

    return 0;
}
