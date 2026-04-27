#include <stdio.h>
#include <stdlib.h>

// -------- VALID DOUBLE --------
double getValidDouble(char *msg) {
    double x;

    while (1) {
        printf("%s", msg);

        if (scanf("%lf", &x) != 1) {
            printf("Invalid input! Enter numeric value.\n");
            while (getchar() != '\n');
        }
        else if (x < 0) {
            printf("Negative values not allowed!\n");
        }
        else {
            return x;
        }
    }
}

// -------- RANGE VALIDATION --------
double getRangeDouble(char *msg, double min, double max) {
    double x;

    while (1) {
        x = getValidDouble(msg);

        if (x < min || x > max)
            printf("Value must be between %.2lf and %.2lf\n", min, max);
        else
            return x;
    }
}

// -------- DIRECTION VALIDATION --------
int getDirection() {
    int d;

    while (1) {
        printf("Enter direction (1 = right, 0 = left): ");

        if (scanf("%d", &d) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
        }
        else if (d != 0 && d != 1) {
            printf("Only 0 or 1 allowed!\n");
        }
        else {
            return d;
        }
    }
}

// -------- STORE INPUT --------
void storeInput(int needDirection) {

    FILE *fp = fopen("./DSA/input.txt", "w");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    double start, end, head, tpt;

    start = getValidDouble("Enter disk start range: ");
    end   = getValidDouble("Enter disk end range: ");

    while (end <= start) {
        printf("End must be greater than start!\n");
        end = getValidDouble("Re-enter disk end range: ");
    }

    int n = (int)getValidDouble("Enter number of requests: ");

    double req[n];

    printf("Enter request sequence:\n");
    for (int i = 0; i < n; i++) {
        char msg[50];
        sprintf(msg, "Request %d: ", i + 1);
        req[i] = getRangeDouble(msg, start, end);
    }

    head = getRangeDouble("Enter head position: ", start, end);

    int dir = -1;

    //  ALWAYS take direction if asked
    if (needDirection) {
        dir = getDirection();
    }

    while (1) {
        printf("Enter seek time per track: ");

        if (scanf("%lf", &tpt) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
        }
        else if (tpt <= 0) {
            printf("Must be greater than 0!\n");
        }
        else {
            break;
        }
    }

    fprintf(fp, "%lf %lf %d\n", start, end, n);

    for (int i = 0; i < n; i++)
        fprintf(fp, "%lf ", req[i]);

    fprintf(fp, "\n%lf %d %lf\n", head, dir, tpt);

    fclose(fp);
}

// -------- MAIN --------
int main() {

    int choice;

    while (1) {

        printf("\n===== DISK SCHEDULER MENU =====\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. SCAN\n");
        printf("4. LOOK\n");
        printf("5. C-SCAN\n");
        printf("6. C-LOOK\n");
        printf("7. Compare All\n");
        printf("8. Exit\n");

        // ✔ FIX: proper validation
        while (1) {
            printf("Enter choice: ");

            if (scanf("%d", &choice) != 1) {
                printf("Invalid input!\n");
                while (getchar() != '\n');
                continue;
            }

            if (choice < 1 || choice > 8) {
                printf("Invalid choice! Please enter 1 to 8.\n");
                continue;
            }

            break;
        }

        if (choice == 8) {
            printf("Exiting...\n");
            break;
        }

        FILE *clr = fopen("./DSA/disk_output.txt", "w");
        if (clr) fclose(clr);

        // ===============================
        // ✔ FIXED LOGIC
        // ===============================

        if (choice == 7) {

            // ✔ TAKE direction input
            storeInput(1);

            system("./DSA/Disk_fcfs < ./DSA/input.txt");   // ignore direction
            system("./DSA/Disk_sstf < ./DSA/input.txt");   // ignore direction
            system("./DSA/Scan < ./DSA/input.txt");   // use direction
            system("./DSA/Look < ./DSA/input.txt");
            system("./DSA/C-Scan < ./DSA/input.txt");
            system("./DSA/C-Look  < ./DSA/input.txt");

            system("./venv/bin/python ./DSA/compare.py");
        }
        else {

            if (choice == 1 || choice == 2)
                storeInput(0);   // no direction needed
            else
                storeInput(1);   // SCAN family needs direction

            switch (choice) {
                case 1: system("./DSA/Disk_fcfs < ./DSA/input.txt"); break;
                case 2: system("./DSA/Disk_sstf < ./DSA/input.txt"); break;
                case 3: system("./DSA/Scan < ./DSA/input.txt"); break;
                case 4: system("./DSA/Look < ./DSA/input.txt"); break;
                case 5: system("./DSA/C-Scan < ./DSA/input.txt"); break;
                case 6: system("./DSA/C-Look < ./DSA/input.txt"); break;
            }

            // system("python Sequence.py");
        }
    }

    return 0;
}