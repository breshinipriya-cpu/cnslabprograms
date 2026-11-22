#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Standard English letter frequencies ordered descending
const char englishOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

const double englishFreq[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75,  7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15,  1.97, 0.07
};

typedef struct {
    char keyMap[26];
    double score;
    char plaintext[512];
} Candidate;

typedef struct {
    char letter;
    int count;
} FreqPair;

int compareFreq(const void *a, const void *b) {
    FreqPair *f1 = (FreqPair *)a;
    FreqPair *f2 = (FreqPair *)b;
    return f2->count - f1->count;
}

int compareCandidates(const void *a, const void *b) {
    Candidate *c1 = (Candidate *)a;
    Candidate *c2 = (Candidate *)b;
    if (c2->score > c1->score) return 1;
    if (c2->score < c1->score) return -1;
    return 0;
}

int main() {
    // Sample monoalphabetic ciphertext
    const char *ciphertext = "WKLV LV D WHVW PHVVDJH IRU PRQRDOSKDEHWLF VXEVWLWXWLRQ FLSKHU DWWDFN";
    printf("======================================================\n");
    printf("   EXPERIMENT 16: FREQUENCY ATTACK ON MONOALPHABETIC   \n");
    printf("                 SUBSTITUTION CIPHER                  \n");
    printf("======================================================\n\n");

    printf("Ciphertext:\n%s\n\n", ciphertext);

    FreqPair cipherFreq[26];
    for (int i = 0; i < 26; i++) {
        cipherFreq[i].letter = 'A' + i;
        cipherFreq[i].count = 0;
    }

    int totalAlpha = 0;
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            cipherFreq[toupper(ciphertext[i]) - 'A'].count++;
            totalAlpha++;
        }
    }

    qsort(cipherFreq, 26, sizeof(FreqPair), compareFreq);

    // Build base mapping from sorted frequencies to ETAOIN...
    char baseMap[26];
    for (int i = 0; i < 26; i++) {
        baseMap[cipherFreq[i].letter - 'A'] = englishOrder[i];
    }

    // Generate top candidate permutations by swapping letters with close frequencies
    Candidate candidates[20];
    int candidateCount = 10;

    for (int k = 0; k < candidateCount; k++) {
        memcpy(candidates[k].keyMap, baseMap, 26);
        // Vary the mapping by swapping adjacent frequent letters
        if (k == 1) { // swap E and T
            char t0 = cipherFreq[0].letter - 'A';
            char t1 = cipherFreq[1].letter - 'A';
            candidates[k].keyMap[t0] = englishOrder[1];
            candidates[k].keyMap[t1] = englishOrder[0];
        } else if (k == 2) { // swap A and O
            char t2 = cipherFreq[2].letter - 'A';
            char t3 = cipherFreq[3].letter - 'A';
            candidates[k].keyMap[t2] = englishOrder[3];
            candidates[k].keyMap[t3] = englishOrder[2];
        } else if (k == 3) { // swap I and N
            char t4 = cipherFreq[4].letter - 'A';
            char t5 = cipherFreq[5].letter - 'A';
            candidates[k].keyMap[t4] = englishOrder[5];
            candidates[k].keyMap[t5] = englishOrder[4];
        } else if (k > 3) {
            int idx1 = (k * 2) % 10;
            int idx2 = (k * 2 + 1) % 10;
            char tA = cipherFreq[idx1].letter - 'A';
            char tB = cipherFreq[idx2].letter - 'A';
            char tmp = candidates[k].keyMap[tA];
            candidates[k].keyMap[tA] = candidates[k].keyMap[tB];
            candidates[k].keyMap[tB] = tmp;
        }

        // Decrypt with keyMap
        double score = 0.0;
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                char orig = toupper(ciphertext[i]);
                char dec = candidates[k].keyMap[orig - 'A'];
                candidates[k].plaintext[i] = islower(ciphertext[i]) ? tolower(dec) : dec;
                score += englishFreq[dec - 'A'];
            } else {
                candidates[k].plaintext[i] = ciphertext[i];
            }
        }
        candidates[k].plaintext[len] = '\0';
        candidates[k].score = score;
    }

    qsort(candidates, candidateCount, sizeof(Candidate), compareCandidates);

    printf("Top 10 Possible Plaintexts (Automated Frequency Analysis):\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Rank | Score   | Decrypted Text Candidate\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("%4d | %7.2f | %s\n", i + 1, candidates[i].score, candidates[i].plaintext);
    }
    printf("--------------------------------------------------------------------------------\n");

    return 0;
}
