#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 10

FILE *logFile;

pthread_mutex_t forks[MAX];
int N;          // number of philosophers
int cycles;     // number of times each philosopher eats

void* philosopher(void* num) {
    int id = *(int*)num;

    for (int i = 0; i < cycles; i++) {

        printf("Philosopher %d is THINKING\n", id);
        fprintf(logFile, "THINKING %d\n", id);
        fflush(logFile);
        sleep(1);

        // Pick forks
        pthread_mutex_lock(&forks[id]);
        printf("Philosopher %d picked LEFT fork %d\n", id, id);

        pthread_mutex_lock(&forks[(id + 1) % N]);
        printf("Philosopher %d picked RIGHT fork %d\n", id, (id + 1) % N);

        // Eating
        printf("Philosopher %d is EATING\n", id);
        fprintf(logFile, "EATING %d\n", id);
        fflush(logFile);
        sleep(1);

        // Release forks
        pthread_mutex_unlock(&forks[id]);
        pthread_mutex_unlock(&forks[(id + 1) % N]);

        printf("Philosopher %d finished EATING\n", id);
    }

    return NULL;
}

int main() {

    logFile = fopen("./SYNC/dining_log.txt", "w");

    pthread_t threads[MAX];
    int ids[MAX];

    // -------- USER INPUT --------
    printf("Enter number of philosophers (max 10): ");
    scanf("%d", &N);

    if (N <= 1 || N > MAX) {
        printf("Invalid number of philosophers.\n");
        return 1;
    }

    printf("Enter number of eating cycles: ");
    scanf("%d", &cycles);

    if (cycles <= 0) {
        printf("Invalid number of cycles.\n");
        return 1;
    }

    // Initialize forks
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    // Create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Join threads
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }


    printf("\nSimulation Completed Successfully.\n");

    fclose(logFile);
    system("python3 ./SYNC/dining_visual.py");
    return 0;
}