#include <stdio.h>
#include <stdint.h>

int main() {
    printf("======================================================\n");
    printf("   EXPERIMENT 29: SHA-3 INTERNAL STATE DIFFUSION      \n");
    printf("======================================================\n\n");

    printf("SHA-3 Specification:\n");
    printf("- State matrix size: 5 x 5 lanes = 25 lanes (each lane 64 bits = 1600 bits)\n");
    printf("- Block size (Rate r): 1024 bits = 16 lanes\n");
    printf("- Capacity c:          576 bits  = 9 lanes\n\n");

    // Matrix representation: 1 = has nonzero bit, 0 = all zeros
    int state[5][5];

    // Initial state after absorbing first message block P0:
    // First 16 lanes (rate) have nonzero bits; 9 capacity lanes are 0.
    int rateLanes = 16;
    int count = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (count < rateLanes) {
                state[x][y] = 1; // Nonzero
            } else {
                state[x][y] = 0; // Zero capacity lane
            }
            count++;
        }
    }

    printf("Initial State Matrix (Round 0) [1 = Nonzero, 0 = Zero]:\n");
    for (int y = 0; y < 5; y++) {
        printf("  Row %d: ", y);
        for (int x = 0; x < 5; x++) {
            printf("%d ", state[x][y]);
        }
        if (y >= 3) printf(" <- Contains zero capacity lanes");
        printf("\n");
    }

    int zeroCount = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (state[x][y] == 0) zeroCount++;
        }
    }
    printf("\nInitial zero lanes in capacity: %d lanes\n\n", zeroCount);

    // SIMULATION OF ROUND 1 (Theta Step):
    // In Keccak-f, the Theta (θ) step computes:
    // C[x] = XOR sum of all 5 lanes in column x
    // D[x] = C[x-1] ^ ROT(C[x+1], 1)
    // A'[x, y] = A[x, y] ^ D[x]
    printf("Diffusion Analysis through Theta (θ) Step in Round 1:\n");
    int C[5] = {0};
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            if (state[x][y] == 1) C[x] = 1; // Column x contains nonzero bits
        }
        printf("  Column %d has nonzero bits? %s\n", x, C[x] ? "YES" : "NO");
    }

    // D[x] combines adjacent column parities:
    int D[5] = {0};
    for (int x = 0; x < 5; x++) {
        D[x] = C[(x + 4) % 5] || C[(x + 1) % 5];
        printf("  D[%d] received diffusion? %s\n", x, D[x] ? "YES" : "NO");
    }

    // Update state lanes
    int nextState[5][5];
    int remainingZeros = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            // A'[x, y] = A[x, y] ^ D[x]
            if (state[x][y] == 1 || D[x] == 1) {
                nextState[x][y] = 1;
            } else {
                nextState[x][y] = 0;
                remainingZeros++;
            }
        }
    }

    printf("\nState Matrix after Round 1 (Theta step):\n");
    for (int y = 0; y < 5; y++) {
        printf("  Row %d: ", y);
        for (int x = 0; x < 5; x++) {
            printf("%d ", nextState[x][y]);
        }
        printf("\n");
    }

    printf("\n======================================================\n");
    printf("CONCLUSION:\n");
    printf("Remaining zero lanes after Round 1 = %d\n", remainingZeros);
    printf("How long does it take before all lanes have at least one nonzero bit?\n");
    printf("ANSWER: Exactly 1 ROUND!\n");
    printf("Due to the Theta step diffusion, D[x] propagates parity from columns\n");
    printf("x-1 and x+1 into every lane (x, y), ensuring all 25 lanes (including all\n");
    printf("9 capacity lanes) become nonzero in the very first round!\n");
    printf("======================================================\n");

    return 0;
}
