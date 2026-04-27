#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// -------- INPUT FUNCTION --------
void storeInput() {
    FILE *fp = fopen("input.txt", "w");

    if (!fp) {
        printf("File error!\n");
        return;
    }

    int frames, n;

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string (space separated):\n");

    int ref[MAX];
    for (int i = 0; i < n; i++) {
        scanf("%d", &ref[i]);
    }

    // store
    fprintf(fp, "%d %d\n", frames, n);

    for (int i = 0; i < n; i++)
        fprintf(fp, "%d ", ref[i]);

    fprintf(fp, "\n");

    fclose(fp);
}

// -------- MAIN --------
int main() {
    int choice;

    while (1) {
        printf("\n===== MEMORY MANAGEMENT MENU =====\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Optimal\n");
        printf("4. Compare All\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 5) break;

        storeInput();

        switch (choice) {
            case 1:
                system("fifo < input.txt");
                break;
            case 2:
                system("lru < input.txt");
                break;
            case 3:
                system("optimal < input.txt");
                break;
            case 4:
                system("fifo < input.txt");
                system("lru < input.txt");
                system("optimal < input.txt");
                break;
        }
    }

    return 0;
}