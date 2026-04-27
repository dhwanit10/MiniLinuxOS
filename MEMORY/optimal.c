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

    int faults = 0;

    printf("\nOptimal Page Replacement\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (f[j] == ref[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1, farthest = i;

            for (int j = 0; j < frames; j++) {
                int k;
                for (k = i + 1; k < n; k++) {
                    if (f[j] == ref[k])
                        break;
                }

                if (k > farthest) {
                    farthest = k;
                    pos = j;
                }
            }

            if (pos == -1) pos = 0;

            f[pos] = ref[i];
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