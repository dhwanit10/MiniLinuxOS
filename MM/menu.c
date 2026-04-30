#include <stdio.h>
#include <stdlib.h>

//////////////// INPUT //////////////////
void takeInput(int blocks[], int *b, int process[], int *p)
{

    do
    {
        printf("Enter number of blocks: ");
        scanf("%d", b);
    } while (*b <= 0);

    printf("\nEnter block sizes (KB):\n");
    for (int i = 0; i < *b; i++)
    {
        do
        {
            printf("Block %d: ", i + 1);
            scanf("%d", &blocks[i]);
        } while (blocks[i] <= 0);
    }

    do
    {
        printf("\nEnter number of processes: ");
        scanf("%d", p);
    } while (*p <= 0);

    printf("\nEnter process sizes (KB):\n");
    for (int i = 0; i < *p; i++)
    {
        do
        {
            printf("Process %d: ", i + 1);
            scanf("%d", &process[i]);
        } while (process[i] <= 0);
    }
}

//////////////// SAVE //////////////////
void saveGraph(char *name, int b, int p, int blocks[], int process[], int alloc[])
{

    FILE *fp = fopen("alloc.txt", "w");

    fprintf(fp, "%s\n%d %d\n", name, b, p);

    for (int i = 0; i < b; i++)
        fprintf(fp, "%d ", blocks[i]);
    fprintf(fp, "\n");

    for (int i = 0; i < p; i++)
        fprintf(fp, "%d ", process[i]);
    fprintf(fp, "\n");

    for (int i = 0; i < p; i++)
        fprintf(fp, "%d ", alloc[i]);

    fclose(fp);
}

//////////////// TABLE //////////////////
void printTable(int process[], int alloc[], int p)
{

    printf("\n=================================\n");
    printf("Process   Size   Block\n");
    printf("---------------------------------\n");

    for (int i = 0; i < p; i++)
    {
        if (alloc[i] != -1)
            printf("P%-8d %-6d B%d\n", i + 1, process[i], alloc[i] + 1);
        else
            printf("P%-8d %-6d Not Allocated\n", i + 1, process[i]);
    }
}

//////////////// FIXED FIRST //////////////////
void fixed_first(int blocks[], int b, int process[], int p,
                 int *internal, int *external, int write)
{
    int alloc[p], used[b];

    for (int i = 0; i < b; i++)
        used[i] = 0;
    for (int i = 0; i < p; i++)
        alloc[i] = -1;

    *internal = *external = 0;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (!used[j] && blocks[j] >= process[i])
            {
                alloc[i] = j;
                used[j] = 1;
                *internal += blocks[j] - process[i];
                break;
            }
        }
    }

    for (int i = 0; i < p; i++)
        if (alloc[i] == -1)
            *external += process[i];

    printTable(process, alloc, p);

    printf("Internal=%d External=%d\n", *internal, *external);

    if (write)
    {
        saveGraph("Fixed First Fit", b, p, blocks, process, alloc);
        system("./venv/bin/python MM/graph.py");
    }
}

//////////////// FIXED BEST //////////////////
void fixed_best(int blocks[], int b, int process[], int p,
                int *internal, int *external, int write)
{
    int alloc[p], used[b];

    for (int i = 0; i < b; i++)
        used[i] = 0;
    for (int i = 0; i < p; i++)
        alloc[i] = -1;

    *internal = *external = 0;

    for (int i = 0; i < p; i++)
    {
        int best = -1;

        for (int j = 0; j < b; j++)
        {
            if (!used[j] && blocks[j] >= process[i])
            {
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }

        if (best != -1)
        {
            alloc[i] = best;
            used[best] = 1;
            *internal += blocks[best] - process[i];
        }
    }

    for (int i = 0; i < p; i++)
        if (alloc[i] == -1)
            *external += process[i];

    printTable(process, alloc, p);

    printf("Internal=%d External=%d\n", *internal, *external);

    if (write)
    {
        saveGraph("Fixed Best Fit", b, p, blocks, process, alloc);
        system("./venv/bin/python MM/graph.py");
    }
}

//////////////// FIXED WORST //////////////////
void fixed_worst(int blocks[], int b, int process[], int p,
                 int *internal, int *external, int write)
{
    int alloc[p], used[b];

    for (int i = 0; i < b; i++)
        used[i] = 0;
    for (int i = 0; i < p; i++)
        alloc[i] = -1;

    *internal = *external = 0;

    for (int i = 0; i < p; i++)
    {
        int worst = -1;

        for (int j = 0; j < b; j++)
        {
            if (!used[j] && blocks[j] >= process[i])
            {
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            alloc[i] = worst;
            used[worst] = 1;
            *internal += blocks[worst] - process[i];
        }
    }

    for (int i = 0; i < p; i++)
        if (alloc[i] == -1)
            *external += process[i];

    printTable(process, alloc, p);

    printf("Internal=%d External=%d\n", *internal, *external);

    if (write)
    {
        saveGraph("Fixed Worst Fit", b, p, blocks, process, alloc);
        system("./venv/bin/python MM/graph.py");
    }
}

//////////////// VARIABLE FIRST //////////////////
void variable_first(int blocks[], int b, int process[], int p,
                    int *internal, int *external, int write)
{
    int alloc[p];

    for (int i = 0; i < p; i++)
        alloc[i] = -1;

    *internal = 0;
    *external = 0;

    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (blocks[j] >= process[i])
            {
                alloc[i] = j;
                blocks[j] -= process[i];
                break;
            }
        }
    }

    for (int i = 0; i < p; i++)
        if (alloc[i] == -1)
            *external += process[i];

    printTable(process, alloc, p);

    printf("Internal=%d External=%d\n", *internal, *external);

    if (write)
    {
        saveGraph("Variable First Fit", b, p, blocks, process, alloc);
        system("./venv/bin/python MM/graph.py");
    }
}

//////////////// VARIABLE BEST //////////////////
void variable_best(int blocks[], int b, int process[], int p,
                   int *internal, int *external, int write)
{
    int alloc[p];

    for (int i = 0; i < p; i++)
        alloc[i] = -1;

    *internal = 0;
    *external = 0;

    for (int i = 0; i < p; i++)
    {
        int best = -1;

        for (int j = 0; j < b; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }

        if (best != -1)
        {
            alloc[i] = best;
            blocks[best] -= process[i];
        }
    }

    for (int i = 0; i < p; i++)
        if (alloc[i] == -1)
            *external += process[i];

    printTable(process, alloc, p);

    printf("Internal=%d External=%d\n", *internal, *external);

    if (write)
    {
        saveGraph("Variable Best Fit", b, p, blocks, process, alloc);
        system("./venv/bin/python MM/graph.py");
    }
}

//////////////// VARIABLE WORST //////////////////
void variable_worst(int blocks[], int b, int process[], int p,
                    int *internal, int *external, int write)
{
    int alloc[p];

    for (int i = 0; i < p; i++)
        alloc[i] = -1;

    *internal = 0;
    *external = 0;

    for (int i = 0; i < p; i++)
    {
        int worst = -1;

        for (int j = 0; j < b; j++)
        {
            if (blocks[j] >= process[i])
            {
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }

        if (worst != -1)
        {
            alloc[i] = worst;
            blocks[worst] -= process[i];
        }
    }

    for (int i = 0; i < p; i++)
        if (alloc[i] == -1)
            *external += process[i];

    printTable(process, alloc, p);

    printf("Internal=%d External=%d\n", *internal, *external);

    if (write)
    {
        saveGraph("Variable Worst Fit", b, p, blocks, process, alloc);
        system("./venv/bin/python MM/graph.py");
    }
}

//////////////// COMPARISON //////////////////
void runComparison(int blocks[], int b, int process[], int p)
{
    int i1,e1,i2,e2,i3,e3,i4,e4,i5,e5,i6,e6;

    int tempBlocks[50];

    // FIXED
    for(int i=0;i<b;i++) tempBlocks[i]=blocks[i];
    fixed_first(tempBlocks,b,process,p,&i1,&e1,1);

    for(int i=0;i<b;i++) tempBlocks[i]=blocks[i];
    fixed_best(tempBlocks,b,process,p,&i2,&e2,1);

    for(int i=0;i<b;i++) tempBlocks[i]=blocks[i];
    fixed_worst(tempBlocks,b,process,p,&i3,&e3,1);

    // VARIABLE
    for(int i=0;i<b;i++) tempBlocks[i]=blocks[i];
    variable_first(tempBlocks,b,process,p,&i4,&e4,1);

    for(int i=0;i<b;i++) tempBlocks[i]=blocks[i];
    variable_best(tempBlocks,b,process,p,&i5,&e5,1);

    for(int i=0;i<b;i++) tempBlocks[i]=blocks[i];
    variable_worst(tempBlocks,b,process,p,&i6,&e6,1);

    // SAVE COMPARISON
    FILE *fp = fopen("compare.txt","w");

    fprintf(fp,"Fixed_First %d %d\n",i1,e1);
    fprintf(fp,"Fixed_Best %d %d\n",i2,e2);
    fprintf(fp,"Fixed_Worst %d %d\n",i3,e3);
    fprintf(fp,"Var_First %d %d\n",i4,e4);
    fprintf(fp,"Var_Best %d %d\n",i5,e5);
    fprintf(fp,"Var_Worst %d %d\n",i6,e6);

    // BEST (min fragmentation)
    int total[6] = {i1+e1,i2+e2,i3+e3,i4+e4,i5+e5,i6+e6};
    int best = 0;

    for(int i=1;i<6;i++)
        if(total[i] < total[best])
            best = i;

    fprintf(fp,"%d",best);
    fclose(fp);

    printf("\nShowing Comparison Graph...\n");
    system("./venv/bin/python MM/comparison.py");
}

//////////////// MAIN //////////////////
int main()
{
    int choice;

    while (1)
    {
        printf("\n===== MAIN MENU =====\n");
        printf("1. Fixed Partition\n");
        printf("2. Variable Partition\n");
        printf("3. Comparison\n");
        printf("4. Exit\n");
        printf("Enter choice: ");

        scanf("%d", &choice);

        if(choice < 1 || choice > 4){
            printf("Invalid Choice!\n");
            continue;
        }

        if (choice == 4){
            printf("\nExiting...\n");
            break;
        }

        int blocks[50], process[50], b, p;
        takeInput(blocks, &b, process, &p);

        if(choice == 3){
            runComparison(blocks,b,process,p);
            continue;
        }

        int sub;
        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n");
        printf("Enter choice: ");
        scanf("%d", &sub);

        if(sub < 1 || sub > 3){
            printf(" Invalid Choice!\n");
            continue;
        }

        int i, e;

        if (choice == 1)
        {
            if (sub == 1)
                fixed_first(blocks, b, process, p, &i, &e, 1);
            else if (sub == 2)
                fixed_best(blocks, b, process, p, &i, &e, 1);
            else
                fixed_worst(blocks, b, process, p, &i, &e, 1);
        }
        else if (choice == 2)
        {
            if (sub == 1)
                variable_first(blocks, b, process, p, &i, &e, 1);
            else if (sub == 2)
                variable_best(blocks, b, process, p, &i, &e, 1);
            else
                variable_worst(blocks, b, process, p, &i, &e, 1);
        }
    }

    return 0;
}