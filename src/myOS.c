#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "scheduling.h"

#define MAX_INPUT 1024
#define MAX_ARGS 64

void parse_input(char *input, char *args[])
{
    int i = 0;

    char *token = strtok(input, " ");

    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " ");
    }

    args[i] = NULL;
}

int main()
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];

    while (1)
    {

        printf("myOS> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\nExiting myOS...\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
        {
            continue;
        }

        parse_input(input, args);

        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting myOS...\n");
            break;
        }

        if (strcmp(args[0], "cd") == 0)
        {

            // cd with no argument → go home
            if (args[1] == NULL)
            {
                chdir(getenv("HOME"));
            }
            else
            {
                if (chdir(args[1]) != 0)
                    perror("cd");
            }

            continue;
        }

        if (strcmp(args[0], "cpu") == 0)
        {

            if (args[1] == NULL)
            {
                printf("Usage: cpu <algorithm>\n");
            }
            else if (strcmp(args[1], "fcfs") == 0)
            {
                run_fcfs();
            }
            else if (strcmp(args[1], "srtf") == 0)
            {
                run_srtf();
            }
            else if (strcmp(args[1], "RR") == 0)
            {
                run_roundrobin();
            }
            else if (strcmp(args[1], "priority") == 0)
            {
                run_priority();
            }
            else
            {
                printf("Unknown algorithm: %s\n", args[1]);
            }

            continue;
        }

        // printf("parsed arguments: \n");
        // for (int i = 0; args[i] != NULL; i++) {
        //     printf("args[%d] = %s\n", i, args[i]);
        // }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Fork failed");
        }
        else if (pid == 0) {
            // Child process
            if (execvp(args[0], args) < 0) {
                perror("Execution failed");
            }
            exit(1);
        }
        else {
            // Parent process
            wait(NULL);
        }

        
    }

    return 0;
}
