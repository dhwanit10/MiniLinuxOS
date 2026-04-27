#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// -------- Input Validation --------
double getValidDouble(char *msg) {
    double x;

    while (1) {
        printf("%s", msg);

        if (scanf("%lf", &x) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
        }
        else if (x < 0) {
            printf("Negative values not allowed!\n");
        }
        else {
            return x;
        }
    }
}

// -------- Range Validation --------
double getRangeDouble(char *msg, double min, double max) {
    double x;

    while (1) {
        x = getValidDouble(msg);

        if (x < min || x > max) {
            printf("Value must be between %.2lf and %.2lf!\n", min, max);
        } else {
            return x;
        }
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

    double req[n];

    printf("Enter request sequence (one by one):\n");
    for (int i = 0; i < n; i++) {
        char msg[50];
        sprintf(msg, "Request %d: ", i + 1);
        req[i] = getRangeDouble(msg, start, end);
    }

    double head = getRangeDouble("Enter initial head position: ", start, end);

    double time_per_track;

    while (1) {
        printf("Enter seek time per track (ms): ");
        if (scanf("%lf", &time_per_track) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
        }
        else if (time_per_track <= 0) {
            printf("Time must be greater than 0!\n");
        }
        else {
            break;
        }
    }

    double total_tracks = 0;

    FILE *fp = fopen("./DSA/disk_output.txt", "a");

    // -------- OUTPUT --------
    printf("\n--- FCFS Disk Scheduling ---\n");
    printf("Disk Range: %.2lf to %.2lf\n", start, end);
    printf("Seek Sequence: %.2lf", head);

    // FILE FORMAT (VERY IMPORTANT)
    fprintf(fp, "FCFS\n");
    fprintf(fp, "Seek Sequence: ");

    for (int i = 0; i < n; i++) {

        total_tracks += fabs(head - req[i]);
        head = req[i];

        printf(" -> %.2lf", head);
        fprintf(fp, "%.2lf ", head);
    }

    double total_seek_time = total_tracks * time_per_track;
    double avg_seek_time = total_seek_time / n;

    fprintf(fp, "FCFS\n");   // <-- algorithm name EXACT
    fprintf(fp, "Total Seek Time: %.2lf ms\n\n", total_seek_time);

    printf("\nTotal Tracks Moved: %.2lf", total_tracks);
    printf("\nTotal Seek Time: %.2lf ms", total_seek_time);
    printf("\nAverage Seek Time: %.2lf ms\n\n", avg_seek_time);

    fprintf(fp, "\n\n");  // spacing important

    fclose(fp);

    // AUTO RUN PYTHON
    system("./venv/bin/python ./DSA/Sequence.py");

    return 0;
}