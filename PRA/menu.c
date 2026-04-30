#include <stdio.h>
#include <stdlib.h>

//////////////////// COMMON ////////////////////
int search(int frames[], int f, int key)
{
    for (int i = 0; i < f; i++)
        if (frames[i] == key)
            return 1;
    return 0;
}

//////////////////// INPUT ////////////////////
void takeInput(int ref[], int *n, int *f)
{

    do
    {
        printf("Enter number of pages (positive only): ");
        scanf("%d", n);
        if (*n <= 0)
            printf("Invalid!\n");
    } while (*n <= 0);

    printf("\nEnter reference string:\n");
    for (int i = 0; i < *n; i++)
    {
        do
        {
            printf("Page %d: ", i + 1);
            scanf("%d", &ref[i]);
            if (ref[i] < 0)
                printf("No negative allowed!\n");
        } while (ref[i] < 0);
    }

    do
    {
        printf("\nEnter number of frames: ");
        scanf("%d", f);
        if (*f <= 0)
            printf("Invalid!\n");
    } while (*f <= 0);
}

//////////////////// FIFO ////////////////////
void fifo_algo(int ref[], int n, int f, int *fault, int *hit, int writeFile)
{

    int frames[f], index = 0;
    *fault = *hit = 0;

    FILE *fp = NULL;

    if (writeFile)
    {
        fp = fopen("output.txt", "w");

        fprintf(fp, "FIFO\n");

        for (int i = 0; i < n; i++)
            fprintf(fp, "%d ", ref[i]);

        fprintf(fp, "\n%d\n", f);
    }

    printf("\n--- FIFO ---\n");

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++)
    {

        if (!search(frames, f, ref[i]))
        {
            frames[index] = ref[i];
            index = (index + 1) % f;
            (*fault)++;
        }
        else
        {
            (*hit)++;
        }

        for (int j = 0; j < f; j++)
        {
            printf("%d ", frames[j]);
            if (writeFile)
                fprintf(fp, "%d ", frames[j]);
        }
        printf("\n");
        if (writeFile)
            fprintf(fp, "\n");
    }

    if (writeFile)
        fclose(fp);
}

//////////////////// LRU ////////////////////
int findLRU(int time[], int f)
{
    int min = time[0], pos = 0;
    for (int i = 1; i < f; i++)
        if (time[i] < min)
        {
            min = time[i];
            pos = i;
        }
    return pos;
}

void lru_algo(int ref[], int n, int f, int *fault, int *hit, int writeFile)
{

    int frames[f], time[f], counter = 0;
    *fault = *hit = 0;

    FILE *fp = NULL;

    if (writeFile)
    {
        fp = fopen("output.txt", "w");

        fprintf(fp, "LRU\n");

        for (int i = 0; i < n; i++)
            fprintf(fp, "%d ", ref[i]);

        fprintf(fp, "\n%d\n", f);
    }

    printf("\n--- LRU ---\n");

    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {

        int found = 0;

        for (int j = 0; j < f; j++)
        {
            if (frames[j] == ref[i])
            {
                found = 1;
                time[j] = ++counter;
                (*hit)++;
                break;
            }
        }

        if (!found)
        {

            int pos = -1;

            for (int j = 0; j < f; j++)
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }

            if (pos == -1)
                pos = findLRU(time, f);

            frames[pos] = ref[i];
            time[pos] = ++counter;
            (*fault)++;
        }

        for (int j = 0; j < f; j++)
        {
            printf("%d ", frames[j]);
            if (writeFile)
                fprintf(fp, "%d ", frames[j]);
        }
        printf("\n");
        if (writeFile)
            fprintf(fp, "\n");
    }

    if (writeFile)
        fclose(fp);
}

//////////////////// OPTIMAL ////////////////////
int predict(int ref[], int frames[], int n, int f, int index)
{

    int pos = -1, far = index;

    for (int i = 0; i < f; i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (frames[i] == ref[j])
            {
                if (j > far)
                {
                    far = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == n)
            return i;
    }

    return (pos == -1) ? 0 : pos;
}

void optimal_algo(int ref[], int n, int f, int *fault, int *hit, int writeFile)
{

    int frames[f];
    *fault = *hit = 0;

    FILE *fp = NULL;

    if (writeFile)
    {
        fp = fopen("output.txt", "w");

        fprintf(fp, "OPTIMAL\n");

        for (int i = 0; i < n; i++)
            fprintf(fp, "%d ", ref[i]);

        fprintf(fp, "\n%d\n", f);
    }

    printf("\n--- OPTIMAL ---\n");

    for (int i = 0; i < f; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++)
    {

        if (!search(frames, f, ref[i]))
        {

            int pos = -1;

            for (int j = 0; j < f; j++)
                if (frames[j] == -1)
                {
                    pos = j;
                    break;
                }

            if (pos == -1)
                pos = predict(ref, frames, n, f, i + 1);

            frames[pos] = ref[i];
            (*fault)++;
        }
        else
        {
            (*hit)++;
        }

        for (int j = 0; j < f; j++)
        {
            printf("%d ", frames[j]);
            if (writeFile)
                fprintf(fp, "%d ", frames[j]);
        }
        printf("\n");
        if (writeFile)
            fprintf(fp, "\n");
    }

    if (writeFile)
        fclose(fp);
}

//////////////////// SINGLE ////////////////////
void runSingle(int type)
{

    int n, f;
    int ref[100];

    takeInput(ref, &n, &f);

    int fault, hit;

    if (type == 1)
        fifo_algo(ref, n, f, &fault, &hit, 1);
    else if (type == 2)
        lru_algo(ref, n, f, &fault, &hit, 1);
    else
        optimal_algo(ref, n, f, &fault, &hit, 1);

    printf("\nPage-Fault=%d\nHit=%d\nHit-Ratio=%.2f\n",
           fault, hit, (float)hit / n);

    system("./venv/bin/python PRA/graph.py");
}

//////////////////// ALL ////////////////////
void runALL()
{
    int n, f;
    int ref[100];

    takeInput(ref, &n, &f);

    int f1, h1, f2, h2, f3, h3;

    printf("\nShowing FIFO Graph...\n");
    fifo_algo(ref, n, f, &f1, &h1, 1);
    system("./venv/bin/python PRA/graph.py");

    printf("\nShowing LRU Graph...\n");
    lru_algo(ref, n, f, &f2, &h2, 1);
    system("./venv/bin/python PRA/graph.py");

    printf("\nShowing OPTIMAL Graph...\n");
    optimal_algo(ref, n, f, &f3, &h3, 1);
    system("./venv/bin/python PRA/graph.py");

    float r1 = (float)h1 / n;
    float r2 = (float)h2 / n;
    float r3 = (float)h3 / n;

    int best = 0;
    if (r3 >= r2 && r3 >= r1)
        best = 2;
    else if (r2 >= r1)
        best = 1;

    // PRINT TABLE WITH ARROW
    printf("\n=========== COMPARISON ===========\n");
    printf("Algo    Fault   Hit   Ratio\n");
    printf("---------------------------------\n");

    printf("FIFO    %d      %d    %.2f %s\n", f1, h1, r1, (best == 0) ? "<-- BEST" : "");
    printf("LRU     %d      %d    %.2f %s\n", f2, h2, r2, (best == 1) ? "<-- BEST" : "");
    printf("OPT     %d      %d    %.2f %s\n", f3, h3, r3, (best == 2) ? "<-- BEST" : "");

    printf("\nBEST ALGORITHM: %s\n",
           best == 2 ? "OPTIMAL" : best == 1 ? "LRU" : "FIFO");

    
    FILE *fp = fopen("compare.txt", "w");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fprintf(fp, "FIFO %d %d %.2f\n", f1, h1, r1);
    fprintf(fp, "LRU %d %d %.2f\n", f2, h2, r2);
    fprintf(fp, "OPTIMAL %d %d %.2f\n", f3, h3, r3);
    fprintf(fp, "%d\n", best);   

    fclose(fp);

    // FINAL COMPARISON GRAPH
    printf("\nShowing Comparison Graph...\n");
    system("./venv/bin/python PRA/comparison.py");
}

//////////////////// MAIN ////////////////////
int main()
{

    int choice;

    while (1)
    {

        printf("\n========= MENU =========\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. OPTIMAL\n");
        printf("4. ALL (Comparison)\n");
        printf("5. EXIT\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            runSingle(1);
        else if (choice == 2)
            runSingle(2);
        else if (choice == 3)
            runSingle(3);
        else if (choice == 4)
            runALL();
        else if (choice == 5)
            break;
        else
            printf("Invalid choice!\n");
    }

    return 0;
}