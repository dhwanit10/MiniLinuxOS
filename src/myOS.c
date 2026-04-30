#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "scheduling.h"
#include "thread.h"
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
    "help",
    "thread process",
    "disk scheduling",
    "page replacement",
    "memory management",
    "fix",
    "ai",
    "explain",
    "code",
    "gpt",
    "process manager",
    "myos",
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

/* =========================================================
                    MYOS HELP SYSTEM
========================================================= */

void print_banner()
{
    printf("\n");

    printf("███╗   ███╗██╗   ██╗ ██████╗ ███████╗\n");
    printf("████╗ ████║╚██╗ ██╔╝██╔═══██╗██╔════╝\n");
    printf("██╔████╔██║ ╚████╔╝ ██║   ██║███████╗\n");
    printf("██║╚██╔╝██║  ╚██╔╝  ██║   ██║╚════██║\n");
    printf("██║ ╚═╝ ██║   ██║   ╚██████╔╝███████║\n");
    printf("╚═╝     ╚═╝   ╚═╝    ╚═════╝ ╚══════╝\n");

    printf("\n");
    printf("═══════════════════════════════════════════════════════════════\n");
    printf("             MYOS TERMINAL - COMMAND CENTER\n");
    printf("═══════════════════════════════════════════════════════════════\n");

    time_t t;
    time(&t);

    printf(" Session Started : %s", ctime(&t));

    printf(" Features:\n");
    printf("   • Native Linux Command Execution\n");
    printf("   • CPU Scheduling Visualizer\n");
    printf("   • Disk Scheduling Algorithms\n");
    printf("   • Page Replacement Algorithms\n");
    printf("   • Memory Management Simulation\n");
    printf("   • AI Command Generator\n");
    printf("   • AI Code Fixer & Explainer\n");
    printf("   • GPT Interactive Chat Mode\n");
    printf("   • Process & Thread Visualization\n");

    printf("═══════════════════════════════════════════════════════════════\n");
    printf(" Type 'help' to view all available MYOS commands.\n");
    printf(" Linux commands like ls, pwd, mkdir, nano, cat, etc also work.\n");
    printf("═══════════════════════════════════════════════════════════════\n\n");
}


/* =========================================================
                    HELP COMMAND
========================================================= */

void show_help()
{
    printf("\n");

    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                     MYOS HELP CENTER                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n");

    printf("\n");

    printf("───────────────────────────────────────────────────────────────\n");
    printf(" BASIC LINUX COMMANDS (All Original Linux Commands Supported)\n");
    printf("───────────────────────────────────────────────────────────────\n");

    printf(" ls                 -> List files and folders\n");
    printf(" pwd                -> Show current directory\n");
    printf(" cd <dir>           -> Change directory\n");
    printf(" mkdir <name>       -> Create folder\n");
    printf(" rmdir <name>       -> Remove folder\n");
    printf(" touch <file>       -> Create file\n");
    printf(" cat <file>         -> View file contents\n");
    printf(" rm <file>          -> Delete file\n");
    printf(" nano <file>        -> Open nano editor\n");
    printf(" clear              -> Clear terminal screen\n");
    printf(" git                -> Git commands supported\n");

    printf("\n");

    printf("───────────────────────────────────────────────────────────────\n");
    printf(" CPU SCHEDULING MODULE\n");
    printf("───────────────────────────────────────────────────────────────\n");

    printf(" cpu fcfs           -> Run FCFS Scheduling Algorithm\n");
    printf(" cpu srtf           -> Run SRTF Scheduling Algorithm\n");
    printf(" cpu RR             -> Run Round Robin Scheduling\n");
    printf(" cpu priority       -> Run Priority Scheduling\n");

    printf("\n");

    printf("───────────────────────────────────────────────────────────────\n");
    printf(" THREAD & PROCESS MODULE\n");
    printf("───────────────────────────────────────────────────────────────\n");

    printf(" thread process     -> Process vs Thread Visualization\n");
    printf(" process manager    -> Launch Process Manager System\n");

    printf("\n");

    printf("───────────────────────────────────────────────────────────────\n");
    printf(" MEMORY & STORAGE MODULES\n");
    printf("───────────────────────────────────────────────────────────────\n");

    printf(" disk scheduling    -> Disk Scheduling Simulator\n");
    printf(" page replacement   -> Page Replacement Algorithms\n");
    printf(" memory management  -> Memory Management Simulator\n");

    printf("\n");

    printf("───────────────────────────────────────────────────────────────\n");
    printf(" AI UTILITIES\n");
    printf("───────────────────────────────────────────────────────────────\n");

    printf(" ai \"task\"          -> Convert Natural Language to Command\n");
    printf(" fix file --auto    -> Automatically Fix Source Code\n");
    printf(" fix file --manual  -> Manual AI Guided Fixing\n");
    printf(" explain file       -> Explain Source Code\n");
    printf(" explain file --detailed -> Detailed Explanation\n");
    printf(" code               -> AI Code Generator\n");
    printf(" gpt                -> Interactive GPT Chat Mode\n");

    printf("\n");

    printf("───────────────────────────────────────────────────────────────\n");
    printf(" SYSTEM COMMANDS\n");
    printf("───────────────────────────────────────────────────────────────\n");

    printf(" help               -> Open MYOS Help Center\n");
    printf(" exit               -> Exit MYOS Terminal\n");

    printf("\n");

    printf("═══════════════════════════════════════════════════════════════\n");
    printf("                     POWERED BY MYOS\n");
    printf("═══════════════════════════════════════════════════════════════\n");

    printf("\n");
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

    print_banner();

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

        /* -------------------------------
                  HELP COMMAND
        --------------------------------*/

        if (strcmp(args[0], "help") == 0)
        {
            show_help();
            free(input);
            continue;
        }
        if (strcmp(args[0], "myos") == 0)
        {
            print_banner();
            free(input);
            continue;
        }
        
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

        if (strcmp(args[0], "thread") == 0)
        {

            if (args[1] == NULL)
            {
                printf("Usage: thread process\n");
            }
            else if (strcmp(args[1], "process") == 0)
            {
                run_thread();
            }
            else
            {
                printf("Unknown command: %s\n", args[1]);
            }

            free(input);
            continue;
        }

        if (strcmp(args[0], "disk") == 0)
        {

            if (args[1] == NULL)
            {
                printf("Usage: disk scheduling\n");
            }
            else if (strcmp(args[1], "scheduling") == 0)
            {
                system("./DSA/menu");
            }
            else
            {
                printf("Unknown command: %s\n", args[1]);
            }

            free(input);
            continue;
        }

        if (strcmp(args[0], "page") == 0)
        {

            if (args[1] == NULL)
            {
                printf("Usage: page replacement\n");
            }
            else if (strcmp(args[1], "replacement") == 0)
            {
                system("./PRA/menu");
            }
            else
            {
                printf("Unknown command: %s\n", args[1]);
            }

            free(input);
            continue;
        }

        if (strcmp(args[0], "memory") == 0)
        {

            if (args[1] == NULL)
            {
                printf("Usage: memory management\n");
            }
            else if (strcmp(args[1], "management") == 0)
            {
                system("./MM/menu");
            }
            else
            {
                printf("Unknown command: %s\n", args[1]);
            }

            free(input);
            continue;
        }

        if (strcmp(args[0], "fix") == 0)
        {
            if (args[1] == NULL || args[2] == NULL)
            {
                printf("Usage: fix <filename> <--auto | --manual>\n");
                free(input);
                continue;
            }
        
            char command[2048];
        
            sprintf(command,
                "./venv/bin/python fix_code.py \"%s\" \"%s\"",
                args[1], args[2]);
            
            system(command);
            
            free(input);
            continue;
        }

        if (strcmp(args[0], "ai") == 0)
        {
            if (args[1] == NULL)
            {
                printf("Usage: ai \"your command\"\n");
                free(input);
                continue;
            }
        
            char ai_command[2048];
        
            // Call Python and store output in temp file
            sprintf(ai_command,
                "./venv/bin/python nlp_to_cmd.py \"%s\" > .ai_cmd.txt",
                input + 3);
            
            system(ai_command);
            
            // Read generated command
            FILE *fp = fopen(".ai_cmd.txt", "r");
            if (!fp)
            {
                perror("Error reading AI output");
                free(input);
                continue;
            }
        
            char generated_cmd[1024];
            fgets(generated_cmd, sizeof(generated_cmd), fp);
            fclose(fp);
        
            // Remove newline
            generated_cmd[strcspn(generated_cmd, "\n")] = 0;
        
            if (strlen(generated_cmd) == 0)
            {
                printf("AI could not generate command.\n");
                free(input);
                continue;
            }
        
            printf("🤖 Suggested Command: %s\n", generated_cmd);
        
            // Confirmation step
            printf("⚠️ Do you want to execute this? (Y/N): ");
            char choice;
            scanf(" %c", &choice);
            getchar(); // clear buffer
        
            if (choice == 'Y' || choice == 'y')
            {
                printf("Executing...\n");
                system(generated_cmd);
            }
            else
            {
                printf("Cancelled.\n");
            }
        
            free(input);
            continue;
        }

        if (strcmp(args[0], "explain") == 0)
        {
            if (args[1] == NULL)
            {
                printf("Usage: explain <filename> [--short | --detailed]\n");
                free(input);
                continue;
            }
        
            char command[2048];
        
            if (args[2] != NULL)
            {
                sprintf(command,
                    "./venv/bin/python explain_code.py \"%s\" \"%s\"",
                    args[1], args[2]);
            }
            else
            {
                sprintf(command,
                    "./venv/bin/python explain_code.py \"%s\"",
                    args[1]);
            }
        
            system(command);
        
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
                "./venv/bin/python ai-agent.py \"%s\"",
                problem);
            
            system(command);
            
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

        /*--------------------------------
             process manager mode
        ----------------------------------*/

        if (strcmp(args[0], "process") == 0)
        {
            char prompt[1024];

            
            if (args[1] == NULL)
            {
                printf("Usage: process manager\n");
            }
            else if (strcmp(args[1], "manager") == 0)
            {
                printf("Entering Process Manager Mode (type '5' to leave)\n");
                system("./venv/bin/python src/process_manager.py");
            }
            else
            {
                printf("Unknown command: %s\n", args[1]);
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