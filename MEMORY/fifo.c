#include <stdio.h>

#define MAX 100

int main() {
    int frames, n;
    scanf("%d %d", &frames, &n);

    int ref[MAX];
    for (int i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    int f[frames];
    for (int i = 0; i < frames; i++) f[i] = -1;

    int faults = 0, idx = 0;

    printf("\nFIFO Page Replacement\n");
    printf("Ref\t");

    for (int i = 0; i < frames; i++) printf("F%d\t", i+1);
    printf("\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (f[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            f[idx] = ref[i];
            idx = (idx + 1) % frames;
            faults++;
        }

        printf("%d\t", ref[i]);
        for (int j = 0; j < frames; j++)
            printf("%d\t", f[j]);
        printf("\n");
    }

    printf("Page Faults = %d\n", faults);
    return 0;
}