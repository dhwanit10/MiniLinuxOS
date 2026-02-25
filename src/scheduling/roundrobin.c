#include <stdio.h>

struct Process
{
    int pid;
    int burstTime;
    int remainingTime;
};

void run_roundrobin()
{
    int n, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter burst time for P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    int time = 0;

    printf("\n--- Round Robin Scheduling ---\n");

    while (1)
    {
        int done = 1;

        for (int i = 0; i < n; i++)
        {
            if (p[i].remainingTime > 0)
            {

                done = 0;

                if (p[i].remainingTime > quantum)
                {
                    time += quantum;
                    p[i].remainingTime -= quantum;
                    printf("Process P%d executed for %d units (Remaining: %d)\n",
                           p[i].pid, quantum, p[i].remainingTime);
                }
                else
                {
                    time += p[i].remainingTime;
                    printf("Process P%d completed (Total Time = %d)\n",
                           p[i].pid, time);
                    p[i].remainingTime = 0;
                }
            }
        }
        if (done)
            break;
    }

}