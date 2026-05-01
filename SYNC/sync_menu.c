#include <stdio.h>
#include <stdlib.h>

FILE *logFile;

void print_header()
{
    printf("\n");

    printf("═══════════════════════════════════════════════\n");
    printf("         SYNCHRONIZATION MODULE\n");
    printf("═══════════════════════════════════════════════\n");

    printf(" 1. Dining Philosopher Problem\n");
    printf(" 2. Producer Consumer Problem\n");
    printf(" 3. Reader Writer Problem\n");
    printf(" 4. Banker's Algorithm\n");
    printf(" 5. About Synchronization\n");
    printf(" 6. Exit\n");

    printf("═══════════════════════════════════════════════\n");
}

void show_about()
{
    printf("\n");

    printf("Synchronization Algorithms Included:\n\n");

    printf("• Dining Philosopher\n");
    printf("  Deadlock prevention using forks/resources.\n\n");

    printf("• Producer Consumer\n");
    printf("  Shared buffer synchronization using semaphores.\n\n");

    printf("• Reader Writer\n");
    printf("  Multiple readers / single writer synchronization.\n\n");

    printf("• Banker's Algorithm\n");
    printf("  Deadlock avoidance algorithm.\n\n");
}

int main()
{
    int choice;

    while (1)
    {
        print_header();

        printf("Enter Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input!\n");

            while (getchar() != '\n');

            continue;
        }

        switch(choice)
        {
            case 1:

                printf("\nLaunching Dining Philosopher...\n");

                system("./SYNC/dining");

                break;

            case 2:

                printf("\nLaunching Producer Consumer...\n");

                system("./SYNC/producer_consumer");

                break;

            case 3:

                printf("\nLaunching Reader Writer...\n");

                system("./SYNC/reader_writer");

                break;

            case 4:

                printf("\nLaunching Banker's Algorithm...\n");

                system("./SYNC/banker");

                break;

            case 5:

                show_about();

                break;

            case 6:

                printf("\nExiting Synchronization Module...\n");

                exit(0);

            default:

                printf("Invalid Choice!\n");
        }
    }

    return 0;
}