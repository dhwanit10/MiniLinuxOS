#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

void* thread_function(void* arg)
{
    int thread_id = *(int*)arg;

    printf("Thread %d is running in Process %d\n", thread_id, getpid());

    pthread_exit(NULL);
}

int main()
{
    int processes, threads;

    printf("Enter number of processes: ");
    scanf("%d", &processes);

    printf("Enter number of threads per process: ");
    scanf("%d", &threads);

    for(int i = 0; i < processes; i++)
    {
        pid_t pid = fork();

        if(pid == 0)
        {
            printf("\nProcess %d created with PID %d\n", i+1, getpid());

            pthread_t tid[threads];
            int thread_id[threads];

            for(int j = 0; j < threads; j++)
            {
                thread_id[j] = j + 1;

                pthread_create(&tid[j], NULL, thread_function, &thread_id[j]);
            }

            for(int j = 0; j < threads; j++)
            {
                pthread_join(tid[j], NULL);
            }

            exit(0);
        }
    }

    for(int i = 0; i < processes; i++)
    {
        wait(NULL);
    }

    printf("\nAll Processes and Threads Finished\n");

    return 0;
}
