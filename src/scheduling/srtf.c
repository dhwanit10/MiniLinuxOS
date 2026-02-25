#include <stdio.h>
#include <limits.h>

#define MAX 100

struct Process {
    int pid;
    int at;
    int bt;
    int rt;
    int ct;
    int tat;
    int wt;
};

void run_srtf() {

    int n;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // INPUT 
    for(int i = 0; i < n; i++) {

        p[i].pid = i + 1;

        printf("\nProcess P%d\n", i+1);

    
        do {
            printf("Arrival Time (>=0): ");
            scanf("%d", &p[i].at);

            if(p[i].at < 0)
                printf("Invalid! Arrival time cannot be negative.\n");

        } while(p[i].at < 0);

    
        do {
            printf("Burst Time (>0): ");
            scanf("%d", &p[i].bt);

            if(p[i].bt <= 0)
                printf("Invalid! Burst time must be positive.\n");

        } while(p[i].bt <= 0);

        p[i].rt = p[i].bt;
    }

    int completed = 0;
    int current_time = 0;

    float total_wt = 0, total_tat = 0;

    // SRTF Scheduling
    while(completed != n) {

        int idx = -1;
        int min_rt = INT_MAX;

        for(int i = 0; i < n; i++) {
            if(p[i].at <= current_time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                idx = i;
            }
        }

        // CPU idle
        if(idx == -1) {
            current_time++;
            continue;
        }

        // execute 1 unit
        p[idx].rt--;
        current_time++;

        if(p[idx].rt == 0) {
            completed++;

            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
        }
    }

    // OUTPUT
    printf("\n============================================================\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("============================================================\n");

    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt);
    }

    printf("============================================================\n");

    printf("Average Waiting Time    : %.2f\n", total_wt/n);
    printf("Average Turnaround Time : %.2f\n", total_tat/n);

}