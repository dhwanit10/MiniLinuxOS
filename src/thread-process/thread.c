#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <readline/readline.h>

FILE *fp1;

void* thread_func(void *arg)
{
    int id = *(int*)arg;

    printf("   Thread %d running in process %d\n", id, getpid());

    fprintf(fp1,"THREAD %d %d\n",getpid(),id);
    fflush(fp1);

    pthread_exit(NULL);
}

int run_thread()
{
    char *input;

    int processes;

    input = readline("Enter number of processes: ");
    processes = atoi(input);
    free(input);

    int thread_counts[processes];

    for(int i=0;i<processes;i++)
    {
        char msg[100];

        sprintf(msg,"Enter threads for process %d: ",i+1);

        input = readline(msg);
        thread_counts[i] = atoi(input);
        free(input);
    }

    fp1 = fopen("process_threads.txt","w");

    for(int i=0;i<processes;i++)
    {
        pid_t pid = fork();

        if(pid==0)
        {
            int threads = thread_counts[i];

            fprintf(fp1,"PROCESS %d\n",getpid());
            fflush(fp1);

            pthread_t tid[threads];
            int ids[threads];

            printf("\nProcess %d created (PID %d)\n",i+1,getpid());

            for(int j=0;j<threads;j++)
            {
                ids[j]=j+1;

                pthread_create(&tid[j],NULL,thread_func,&ids[j]);
            }

            for(int j=0;j<threads;j++)
                pthread_join(tid[j],NULL);

            fclose(fp1);
            exit(0);
        }

        wait(NULL);
    }

    fclose(fp1);

    system("./venv/bin/python src/thread-process/thread-graph.py");

    return 0;
}