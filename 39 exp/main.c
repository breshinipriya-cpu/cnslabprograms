#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Standard English letter frequencies
const double englishFreq[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75,  7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15,  1.97, 0.07
};

typedef struct {
    int shift;
    double score;
    char text[512];
} DecryptionCandidate;

int compare(const void *a, const void *b) {
    DecryptionCandidate *c1 = (DecryptionCandidate *)a;
    DecryptionCandidate *c2 = (DecryptionCandidate *)b;
    if (c2->score > c1->score) return 1;
    if (c2->score < c1->score) return -1;
    return 0;
}

int main() {
    char ciphertext[512] = "LIPPS ASVPH XLMW MW ER EHHMXMZI GMTLIV EXXEGO XIWX";
    DecryptionCandidate candidates[26];
    int topN = 10;

    printf("======================================================\n");
    printf("   EXPERIMENT 39: FREQUENCY ATTACK ON ADDITIVE CIPHER \n");
    printf("======================================================\n\n");

    printf("Ciphertext: %s\n\n", ciphertext);

    int len = strlen(ciphertext);

    // Evaluate all 26 possible shift keys
    for (int k = 0; k < 26; k++) {
        candidates[k].shift = k;
        int counts[26] = {0};
        int totalLetters = 0;

        for (int i = 0; i < len; i++) {
            char ch = ciphertext[i];
            if (isupper(ch)) {
                char dec = (ch - 'A' - k + 26) % 26 + 'A';
                candidates[k].text[i] = dec;
                counts[dec - 'A']++;
                totalLetters++;
            } else if (islower(ch)) {
                char dec = (ch - 'a' - k + 26) % 26 + 'a';
                candidates[k].text[i] = dec;
                counts[dec - 'a']++;
                totalLetters++;
            } else {
                candidates[k].text[i] = ch;
            }
        }
        candidates[k].text[len] = '\0';

        // Calculate frequency correlation score
        double score = 0.0;
        if (totalLetters > 0) {
            for (int i = 0; i < 26; i++) {
                double observed = ((double)counts[i] / totalLetters) * 100.0;
                score += observed * englishFreq[i];
            }
        }
        candidates[k].score = score;
    }

    qsort(candidates, 26, sizeof(DecryptionCandidate), compare);

    printf("Top %d Most Likely Plaintexts (Ranked Automatically):\n", topN);
    printf("--------------------------------------------------------------------------------\n");
    printf("Rank | Shift | Score   | Decrypted Text Candidate\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < topN && i < 26; i++) {
        printf("%4d |   %2d  | %7.2f | %s\n",
               i + 1, candidates[i].shift, candidates[i].score, candidates[i].text);
    }
    printf("--------------------------------------------------------------------------------\n");

    return 0;
}
