#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 100
#define EPS 0.00001



int run_priority() {

    FILE *fp = fopen("gantt_data.txt","w");

    int n;

    do {
        printf("Enter number of processes (1-100): ");
        scanf("%d", &n);
        if(n <= 0 || n > MAX)
            printf("Invalid! Enter between 1 and 100.\n");
    } while(n <= 0 || n > MAX);

    int pid[MAX], priority[MAX];
    float at[MAX], bt[MAX], rt[MAX], ct[MAX], tat[MAX], wt[MAX];

    for(int i = 0; i < n; i++) {

        pid[i] = i + 1;

        printf("\nProcess %d\n", pid[i]);

        do {
            printf("Arrival Time (>=0): ");
            scanf("%f", &at[i]);
            if(at[i] < 0)
                printf("Arrival time cannot be negative.\n");
        } while(at[i] < 0);

        do {
            printf("Burst Time (>0): ");
            scanf("%f", &bt[i]);
            if(bt[i] <= 0)
                printf("Burst time must be greater than 0.\n");
        } while(bt[i] <= 0);

        printf("Priority (smaller number = higher priority): ");
        scanf("%d", &priority[i]);

        rt[i] = bt[i];
    }

    float csOverhead;

    do {
        printf("\nEnter Context Switch Overhead Time (>=0): ");
        scanf("%f", &csOverhead);
        if(csOverhead < 0)
            printf("Overhead cannot be negative.\n");
    } while(csOverhead < 0);

    float time = 0;
    int completed = 0;
    int lastProcess = -1;
    int contextSwitch = 0;

    printf("\nExecution Timeline:\n");

    while(completed < n) {

        int current = -1;
        int bestPriority = INT_MAX;

        for(int i = 0; i < n; i++) {

            if(at[i] <= time + EPS && rt[i] > EPS) {

                if(current == -1 ||
                   priority[i] < bestPriority ||
                   (priority[i] == bestPriority && at[i] < at[current]) ||
                   (priority[i] == bestPriority && fabs(at[i] - at[current]) < EPS && pid[i] < pid[current])) {

                    bestPriority = priority[i];
                    current = i;
                }
            }
        }

        // CPU Idle
        if(current == -1) {

            float nextArrival = FLT_MAX;

            for(int i = 0; i < n; i++)
                if(rt[i] > EPS && at[i] > time && at[i] < nextArrival)
                    nextArrival = at[i];

            printf("Idle (%.2f -> %.2f)\n", time, nextArrival);

            fprintf(fp,"IDLE %.2f %.2f\n", time, nextArrival-time);

            time = nextArrival;
            continue;
        }

        // Context Switch
        if(lastProcess != -1 && lastProcess != current) {

            contextSwitch++;

            if(csOverhead > 0) {

                printf("Context Switch (%.2f -> %.2f)\n",
                       time, time + csOverhead);

                fprintf(fp,"CS %.2f %.2f\n", time, csOverhead);

                time += csOverhead;
            }
        }

        float nextArrival = FLT_MAX;

        for(int i = 0; i < n; i++)
            if(at[i] > time && rt[i] > EPS && at[i] < nextArrival)
                nextArrival = at[i];

        float executeTime;

        if(nextArrival == FLT_MAX)
            executeTime = rt[current];
        else
            executeTime = fmin(rt[current], nextArrival - time);

        printf("P%d (%.2f -> %.2f)\n",
               pid[current], time, time + executeTime);

        fprintf(fp,"P%d %.2f %.2f\n",
                pid[current], time, executeTime);

        rt[current] -= executeTime;
        time += executeTime;

        if(rt[current] <= EPS) {

            ct[current] = time;
            tat[current] = ct[current] - at[current];
            wt[current] = tat[current] - bt[current];

            if(wt[current] < 0)
                wt[current] = 0;

            completed++;
        }

        lastProcess = current;
    }

    float totalWT = 0, totalTAT = 0;

    printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");

    for(int i = 0; i < n; i++) {

        totalWT += wt[i];
        totalTAT += tat[i];

        printf("P%d\t%.2f\t%.2f\t%d\t%.2f\t%.2f\t%.2f\n",
               pid[i], at[i], bt[i], priority[i],
               ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWT/n);
    printf("Average Turnaround Time: %.2f\n", totalTAT/n);
    printf("Total Context Switches: %d\n", contextSwitch);

    fclose(fp);

    system("./venv/bin/python src/scheduling/ganttchart.py");
    return 0;
}