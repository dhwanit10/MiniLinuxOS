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

    double start=getValidDouble("Enter disk start range: ");
    double end=getValidDouble("Enter disk end range: ");

    while (end <= start) {
        printf("End must be greater than start!\n");
        end = getValidDouble("Re-enter disk end range: ");
    }

    int n;
    printf("Enter total number of requests: ");
    scanf("%d",&n);

    double req[n];

    printf("Enter requests Sequence:\n");
    for(int i=0;i<n;i++){
        char msg[50];
        sprintf(msg,"Request %d: ",i+1);
        req[i]=getRangeDouble(msg,start,end);
    }

    double head=getRangeDouble("Enter initial head position: ",start,end);
    int direction=getDirection();
    double tpt=getValidDouble("Enter seek time per track: ");

    sort(req,n);

    double total=0;
    FILE *fp=fopen("./DSA/disk_output.txt","a");

    printf("\n--- C-LOOK ---\n");
    printf("Seek Sequence: %.2lf",head);

    fprintf(fp, "C-LOOK\n");
    fprintf(fp, "Seek Sequence: ");

    int i;
    for(i=0;i<n;i++) 
        if(req[i]>head) break;

    // -------- RIGHT DIRECTION --------
    if(direction==1){

        for(int j=i;j<n;j++){
            total+=fabs(head-req[j]);
            head=req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }

        if(i>0){
            total+=fabs(head-req[0]);
            head=req[0];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }

        for(int j=1;j<i;j++){
            total+=fabs(head-req[j]);
            head=req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }
    }

    // -------- LEFT DIRECTION (FIXED) --------
    else {

        for(int j=i-1;j>=0;j--){
            total+=fabs(head-req[j]);
            head=req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }

        if(i<n){
            total+=fabs(head-req[n-1]);
            head=req[n-1];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }

        for(int j=n-2;j>=i;j--){
            total+=fabs(head-req[j]);
            head=req[j];
            printf(" -> %.2lf",head);
            fprintf(fp,"%.2lf ",head);
        }
    }

    double total_seek=total*tpt;
    double avg=total_seek/n;
    fprintf(fp, "C-LOOK\n");   // <-- algorithm name EXACT
    fprintf(fp, "Total Seek Time: %.2lf ms\n\n", total_seek);

    printf("\nTotal Tracks: %.2lf",total);
    printf("\nTotal Seek Time: %.2lf ms",total_seek);
    printf("\nAverage Seek Time: %.2lf ms\n",avg);

    fprintf(fp,"\nTotal Tracks: %.2lf",total);
    fprintf(fp,"\nTotal Seek Time: %.2lf ms",total_seek);
    fprintf(fp,"\nAverage Seek Time: %.2lf ms\n",avg);

    fclose(fp);

    system("./venv/bin/python ./DSA/Sequence.py");

    return 0;
}