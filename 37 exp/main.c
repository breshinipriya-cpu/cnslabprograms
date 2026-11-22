#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Standard English letter frequency distribution
const char englishOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

const double englishFreq[26] = {
    8.17, 1.49, 2.78, 4.25, 12.70, 2.23, 2.02, 6.09, 6.97, 0.15,
    0.77, 4.03, 2.41, 6.75,  7.51, 1.93, 0.10, 5.99, 6.33, 9.06,
    2.76, 0.98, 2.36, 0.15,  1.97, 0.07
};

typedef struct {
    char keyMap[26];
    double score;
    char text[512];
} Candidate;

typedef struct {
    char ch;
    int count;
} Freq;

int cmpFreq(const void *a, const void *b) {
    return ((Freq *)b)->count - ((Freq *)a)->count;
}

int cmpCand(const void *a, const void *b) {
    if (((Candidate *)b)->score > ((Candidate *)a)->score) return 1;
    if (((Candidate *)b)->score < ((Candidate *)a)->score) return -1;
    return 0;
}

int main() {
    const char *ciphertext = "DAHHK SKNHZ PDEO EO W IEDDWLXEWXEAC OQXOPEPQPEKJ YELDAN";
    printf("======================================================\n");
    printf("   EXPERIMENT 37: MONOALPHABETIC FREQUENCY ATTACK     \n");
    printf("======================================================\n\n");

    printf("Ciphertext:\n%s\n\n", ciphertext);

    Freq f[26];
    for (int i = 0; i < 26; i++) {
        f[i].ch = 'A' + i;
        f[i].count = 0;
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            f[toupper(ciphertext[i]) - 'A'].count++;
        }
    }

    qsort(f, 26, sizeof(Freq), cmpFreq);

    char baseMap[26];
    for (int i = 0; i < 26; i++) {
        baseMap[f[i].ch - 'A'] = englishOrder[i];
    }

    Candidate candidates[10];
    for (int k = 0; k < 10; k++) {
        memcpy(candidates[k].keyMap, baseMap, 26);
        // Vary key mapping for different permutations
        if (k > 0) {
            int i1 = (k * 2) % 12;
            int i2 = (k * 2 + 1) % 12;
            char c1 = f[i1].ch - 'A';
            char c2 = f[i2].ch - 'A';
            char temp = candidates[k].keyMap[c1];
            candidates[k].keyMap[c1] = candidates[k].keyMap[c2];
            candidates[k].keyMap[c2] = temp;
        }

        double score = 0.0;
        for (int i = 0; i < len; i++) {
            if (isalpha(ciphertext[i])) {
                char dec = candidates[k].keyMap[toupper(ciphertext[i]) - 'A'];
                candidates[k].text[i] = islower(ciphertext[i]) ? tolower(dec) : dec;
                score += englishFreq[dec - 'A'];
            } else {
                candidates[k].text[i] = ciphertext[i];
            }
        }
        candidates[k].text[len] = '\0';
        candidates[k].score = score;
    }

    qsort(candidates, 10, sizeof(Candidate), cmpCand);

    printf("Top 10 Possible Plaintexts Ranked by Frequency Likelihood:\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("Rank | Score   | Decrypted Text Candidate\n");
    printf("--------------------------------------------------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        printf("%4d | %7.2f | %s\n", i + 1, candidates[i].score, candidates[i].text);
    }
    printf("--------------------------------------------------------------------------------\n");

    return 0;
}
