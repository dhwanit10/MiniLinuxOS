#include <stdio.h>

#define MAX 100

int main() {
    int frames, n;
    scanf("%d %d", &frames, &n);

    int ref[MAX];
    for (int i = 0; i < n; i++)
        scanf("%d", &ref[i]);

    int f[frames], time[frames];
    for (int i = 0; i < frames; i++) {
        f[i] = -1;
        time[i] = 0;
    }

    int faults = 0, counter = 0;

    printf("\nLRU Page Replacement\n");

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frames; j++) {
            if (f[j] == ref[i]) {
                found = 1;
                time[j] = ++counter;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[lru])
                    lru = j;
            }

            f[lru] = ref[i];
            time[lru] = ++counter;
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