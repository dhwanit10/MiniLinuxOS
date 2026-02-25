#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int priority;
};

void run_priority() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter burst time for P%d: ", i+1);
        scanf("%d", &p[i].burstTime);

        printf("Enter priority for P%d: ", i+1);
        scanf("%d", &p[i].priority);

        p[i].pid = i+1;
    }

    // Sort by priority (simple bubble sort)
    for(int i=0; i<n-1; i++) {
        for(int j=i+1; j<n; j++) {
            if(p[i].priority > p[j].priority) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    printf("\n--- Priority Scheduling ---\n");
    int time = 0;

    for(int i=0; i<n; i++) {
        time += p[i].burstTime;
        printf("Process P%d executed (Priority: %d, Completion Time: %d)\n",
               p[i].pid, p[i].priority, time);
    }

}