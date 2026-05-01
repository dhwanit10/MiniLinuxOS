#include <stdio.h>

#define MAX 10

int main() {

    int n, m; // n = processes, m = resources
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int avail[MAX];
    int finish[MAX] = {0};
    int safeSeq[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &avail[i]);
    }

    // Need Matrix = Max - Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {

            if (!finish[i]) {

                int j;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j])
                        break;
                }

                if (j == m) {
                    // process can execute
                    for (int k = 0; k < m; k++) {
                        avail[k] += alloc[i][k];
                    }

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\nSystem is NOT in safe state (Deadlock possible)\n");
            return 0;
        }
    }

    printf("\nSystem is in SAFE STATE\nSafe sequence: ");

    for (int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    printf("\n");

    return 0;
}