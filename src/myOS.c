#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "scheduling.h"
#include <readline/readline.h>
#include <readline/history.h>

// #define MAX_INPUT 1024
#define MAX_ARGS 64

/* -------------------------------
   Command list for autocomplete
--------------------------------*/

char *commands[] = {
    "ls",
    "cd",
    "pwd",
    "mkdir",
    "rmdir",
    "git",
    "add",
    "status",
    "top",
    "commit",
    "push",
    "pull",
    "rm",
    "top",
    "touch",
    "cat",
    "nano",
    "clear",
    "cpu",
    "fcfs",
    "srtf",
    "RR",
    "priority",
    "exit",
    NULL};

char *file_generator(const char *text, int state)
{
    static DIR *dir;
    static struct dirent *entry;
    static int len;

    if (!state)
    {
        dir = opendir(".");
        len = strlen(text);
    }

    if (!dir)
        return NULL;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, text, len) == 0)
        {
            return strdup(entry->d_name);
        }
    }

    closedir(dir);
    return NULL;
}

/* -------------------------------
   Autocomplete generator
--------------------------------*/

char *command_generator(const char *text, int state)
{
    static int index, len;
    char *name;

    if (!state)
    {
        index = 0;
        len = strlen(text);
    }

    while ((name = commands[index++]))
    {
        if (strncmp(name, text, len) == 0)
        {
            return strdup(name);
        }
    }

    return NULL;
}

/* -------------------------------
   Completion function
--------------------------------*/

char **command_completion(const char *text, int start, int end)
{
    if (start == 0)
    {
        return rl_completion_matches(text, command_generator);
    }

    return NULL;
}

/* -------------------------------
   Parse user input
--------------------------------*/

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

/* -------------------------------
   Main shell
--------------------------------*/

int main()
{
    char *input;
    char *args[MAX_ARGS];

    /* Enable TAB completion */
    rl_attempted_completion_function = command_completion;

    while (1)
    {

        input = readline("myOS> ");

        if (input == NULL)
        {
            printf("\nExiting myOS...\n");
            break;
        }

        if (strlen(input) == 0)
        {
            free(input);
            continue;
        }

        /* Save command in history */
        add_history(input);

        parse_input(input, args);

        if (strcmp(args[0], "exit") == 0)
        {
            printf("Exiting myOS...\n");
            free(input);
            break;
        }

        /* -------------------------------
           CD command
        --------------------------------*/

        if (strcmp(args[0], "cd") == 0)
        {

            if (args[1] == NULL)
            {
                chdir(getenv("HOME"));
            }
            else
            {
                if (chdir(args[1]) != 0)
                    perror("cd");
            }

            free(input);
            continue;
        }

        /* -------------------------------
           CPU scheduling commands
        --------------------------------*/

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

            free(input);
            continue;
        }

        /*--------------------------------
            Ai Agent code
        ----------------------------------*/

        if (strcmp(args[0], "code") == 0)
        {
            char problem[1024];

            printf("Enter problem statement:\n");
            fgets(problem, sizeof(problem), stdin);

            problem[strcspn(problem, "\n")] = 0;

            char command[2048];

            sprintf(command,
                    "./venv/bin/python ai-agent.py \"%s\" > generated_code.txt",
                    problem);

            system(command);

            printf("Code generated and saved to generated_code.txt\n");

            free(input);
            continue;
        }

        /*--------------------------------
             GPT Chat Mode
        ----------------------------------*/

        if (strcmp(args[0], "gpt") == 0)
        {
            char prompt[1024];

            printf("Entering GPT Chat Mode (type 'exit' to leave)\n");

            while (1)
            {
                printf("gpt> ");
                fgets(prompt, sizeof(prompt), stdin);

                prompt[strcspn(prompt, "\n")] = 0;

                if (strcmp(prompt, "exit") == 0)
                {
                    printf("Leaving GPT mode...\n");
                    break;
                }

                char command[2048];

                sprintf(command,
                        "./venv/bin/python chat-gpt.py \"%s\"",
                        prompt);

                system(command);

                printf("\n");
            }

            free(input);
            continue;
        }

        /* -------------------------------
           Execute normal Linux command
        --------------------------------*/

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
        }
        else if (pid == 0)
        {
            if (execvp(args[0], args) < 0)
            {
                perror("Execution failed");
            }
            exit(1);
        }
        else
        {
            wait(NULL);
        }

        free(input);
    }

    return 0;
}