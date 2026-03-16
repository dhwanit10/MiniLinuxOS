#include <stdio.h>
#include <stdlib.h>
#define MAX 100



struct Process {
    int pid;
    float at;
    float bt;
    float ct;
    float tat;
    float wt;
};

int run_fcfs() {

    int n;
    struct Process p[MAX], temp;

    FILE *fp  = fopen("gantt_data.txt","w");

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // INPUT
    for(int i = 0; i < n; i++) {

        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i+1);

        do {
            printf("Arrival Time (>=0): ");
            scanf("%f", &p[i].at);

            if(p[i].at < 0)
                printf("Invalid! Arrival time cannot be negative.\n");

        } while(p[i].at < 0);

        do {
            printf("Burst Time (>0): ");
            scanf("%f", &p[i].bt);

            if(p[i].bt <= 0)
                printf("Invalid! Burst time must be positive.\n");

        } while(p[i].bt <= 0);
    }

    // SORT BY ARRIVAL TIME
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    float current_time = 0;
    float total_wt = 0, total_tat = 0;

    printf("\nExecution Timeline:\n");

    for(int i = 0; i < n; i++) {

        // CPU Idle case
        if(current_time < p[i].at) {

            printf("Idle (%.2f -> %.2f)\n", current_time, p[i].at);

            fprintf(fp,"IDLE %.2f %.2f\n",
                    current_time,
                    p[i].at - current_time);

            current_time = p[i].at;
        }

        printf("P%d (%.2f -> %.2f)\n",
               p[i].pid,
               current_time,
               current_time + p[i].bt);

        fprintf(fp,"P%d %.2f %.2f\n",
                p[i].pid,
                current_time,
                p[i].bt);

        current_time += p[i].bt;

        p[i].ct = current_time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    // OUTPUT TABLE
    printf("\n============================================================\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("============================================================\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("============================================================\n");

    printf("Average Waiting Time    : %.2f\n", total_wt/n);
    printf("Average Turnaround Time : %.2f\n", total_tat/n);

    fclose(fp);

     system("./venv/bin/python src/scheduling/ganttchart.py");
    return 0;
}