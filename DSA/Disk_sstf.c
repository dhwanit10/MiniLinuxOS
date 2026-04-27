#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// -------- Input Validation --------
double getValidDouble(char *msg) {
    double x;
    while (1) {
        printf("%s", msg);

        if (scanf("%lf", &x) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
        } else if (x < 0) {
            printf("Negative not allowed!\n");
        } else {
            return x;
        }
    }
}

double getRangeDouble(char *msg, double min, double max) {
    double x;
    while (1) {
        x = getValidDouble(msg);

        if (x < min || x > max)
            printf("Value must be between %.2lf and %.2lf\n", min, max);
        else
            return x;
    }
}

// -------- MAIN --------
int main() {

    double start, end;

    start = getValidDouble("Enter disk start range: ");
    end   = getValidDouble("Enter disk end range: ");

    while (end <= start) {
        printf("End must be greater than start!\n");
        end = getValidDouble("Re-enter disk end range: ");
    }

    int n = (int)getValidDouble("Enter total number of requests: ");

    if (n <= 0) {
        printf("No requests!\n");
        return 0;
    }

    double req[n];
    int visited[n];

    memset(visited, 0, sizeof(visited));

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        char msg[50];
        sprintf(msg, "Request %d: ", i + 1);
        req[i] = getRangeDouble(msg, start, end);
    }

    double head = getRangeDouble("Enter initial head position: ", start, end);
    double time_per_track = getValidDouble("Enter seek time per track: ");

    double total_tracks = 0;

    FILE *fp = fopen("./DSA/disk_output.txt", "a");
    if (fp == NULL) {
        printf("File error!\n");
        return 1;
    }

    printf("\n--- SSTF ---\n");
    printf("Seek Sequence: %.2lf", head);

    fprintf(fp, "SSTF\n");
    fprintf(fp, "Seek Sequence: %.2lf ", head);

    // -------- SSTF Logic --------
    for (int i = 0; i < n; i++) {

        double min_dist = 1e9;
        int index = -1;

        for (int j = 0; j < n; j++) {

            if (!visited[j]) {

                double dist = fabs(head - req[j]);

                // ✔ priority selection
                if (dist < min_dist) {
                    min_dist = dist;
                    index = j;
                }
            }
        }

        // safety check
        if (index == -1) break;

        visited[index] = 1;

        total_tracks += min_dist;
        head = req[index];

        printf(" -> %.2lf", head);
        fprintf(fp, "-> %.2lf ", head);
    }

    double total_seek = total_tracks * time_per_track;
    double avg_seek = total_seek / n;

    printf("\n\nTotal Tracks: %.2lf", total_tracks);
    printf("\nTotal Seek Time: %.2lf ms", total_seek);
    printf("\nAverage Seek Time: %.2lf ms\n", avg_seek);

    fprintf(fp, "\nTotal Seek Time: %.2lf ms\n\n", total_seek);

    fclose(fp);

    system("./venv/bin/python ./DSA/Sequence.py");

    return 0;
}