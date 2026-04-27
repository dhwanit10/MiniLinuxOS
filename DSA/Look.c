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
        } else if (x < 0) {
            printf("Negative not allowed!\n");
        } else return x;
    }
}

double getRangeDouble(char *msg, double min, double max) {
    double x;
    while (1) {
        x = getValidDouble(msg);
        if (x < min || x > max)
            printf("Value must be between %.2lf and %.2lf\n", min, max);
        else return x;
    }
}

int getDirection() {
    int d;
    while (1) {
        printf("Enter direction (1 = right, 0 = left): ");
        if (scanf("%d", &d) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
        } else if (d != 0 && d != 1) {
            printf("Only 0 or 1 allowed!\n");
        } else return d;
    }
}

// -------- Sorting --------
void sort(double arr[], int n) {
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(arr[j] > arr[j+1]) {
                double t = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = t;
            }
}

// -------- MAIN --------
int main() {

    double start = getValidDouble("Enter disk start range: ");
    double end   = getValidDouble("Enter disk end range: ");

    while (end <= start) {
        printf("End must be greater than start!\n");
        end = getValidDouble("Re-enter disk end range: ");
    }

    int n = (int)getValidDouble("Enter total number of requests: ");
    double req[n];

    printf("Enter requests Sequence:\n");
    for(int i=0;i<n;i++) {
        char msg[50];
        sprintf(msg,"Request %d: ",i+1);
        req[i] = getRangeDouble(msg,start,end);
    }

    double head = getRangeDouble("Enter initial head position: ",start,end);
    int direction = getDirection();
    double tpt = getValidDouble("Enter seek time per track (ms): ");

    sort(req,n);

    double total = 0;

    FILE *fp = fopen("./DSA/disk_output.txt","a");

    printf("\n--- LOOK Disk Scheduling ---\n");
    printf("Seek Sequence: %.2lf",head);

    fprintf(fp, "LOOK\n");
    fprintf(fp, "Seek Sequence: ");

    int i;
    for(i=0;i<n;i++) if(req[i]>head) break;

    if(direction==1){
        for(int j=i;j<n;j++){
            total += fabs(head - req[j]);
            head = req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }
        for(int j=i-1;j>=0;j--){
            total += fabs(head - req[j]);
            head = req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }
    } else {
        for(int j=i-1;j>=0;j--){
            total += fabs(head - req[j]);
            head = req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }
        for(int j=i;j<n;j++){
            total += fabs(head - req[j]);
            head = req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }
    }

    //  Calculations
    double total_seek_time = total * tpt;
    double avg_seek_time = total_seek_time / n;
    fprintf(fp, "LOOK\n");   // <-- algorithm name EXACT
    fprintf(fp, "Total Seek Time: %.2lf ms\n\n", total_seek_time);

    // -------- OUTPUT --------
    printf("\nTotal Tracks Moved: %.2lf", total);
    printf("\nSeek Time per Track: %.2lf ms", tpt);
    printf("\nTotal Seek Time: %.2lf ms", total_seek_time);
    printf("\nAverage Seek Time: %.2lf ms\n", avg_seek_time);

    // -------- FILE WRITE --------
    fprintf(fp,"\nTotal Tracks Moved: %.2lf", total);
    fprintf(fp,"\nSeek Time per Track: %.2lf ms", tpt);
    fprintf(fp,"\nTotal Seek Time: %.2lf ms", total_seek_time);
    fprintf(fp,"\nAverage Seek Time: %.2lf ms\n\n", avg_seek_time);

    fclose(fp);

    // Auto graph
    system("./venv/bin/python ./DSA/Sequence.py");

    return 0;
}