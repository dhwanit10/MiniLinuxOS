#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

FILE *logFile;

int read_count = 0;
int data = 0;

pthread_mutex_t mutex;
pthread_mutex_t wrt;

int num_readers, num_writers;
int cycles;

// -------- Reader Function --------
void* reader(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < cycles; i++) {

        // Entry section
        pthread_mutex_lock(&mutex);
        read_count++;

        if (read_count == 1)
            pthread_mutex_lock(&wrt); // block writers

        pthread_mutex_unlock(&mutex);

        // Reading
        printf("Reader %d is READING data = %d\n", id, data);
        sleep(1);

        fprintf(logFile,
        "READER %d %d\n",
        id,
        data);

        fflush(logFile);

        // Exit section
        pthread_mutex_lock(&mutex);
        read_count--;

        if (read_count == 0)
            pthread_mutex_unlock(&wrt); // allow writers

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}

// -------- Writer Function --------
void* writer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < cycles; i++) {

        pthread_mutex_lock(&wrt);

        // Writing
        data++;
        printf("Writer %d is WRITING data = %d\n", id, data);
        sleep(2);

        fprintf(logFile,
        "WRITER %d %d\n",
        id,
        data);

        fflush(logFile);

        pthread_mutex_unlock(&wrt);

        sleep(1);
    }

    return NULL;
}

int main() {

    logFile = fopen("./SYNC/readerwriter_log.txt", "w");
    
    system("venv/bin/python ./SYNC/readerwriter_visual.py &");
    sleep(1);

    pthread_t r_threads[MAX], w_threads[MAX];
    int r_ids[MAX], w_ids[MAX];

    // -------- USER INPUT --------
    printf("Enter number of readers: ");
    scanf("%d", &num_readers);

    printf("Enter number of writers: ");
    scanf("%d", &num_writers);

    printf("Enter number of cycles: ");
    scanf("%d", &cycles);

    if (num_readers <= 0 || num_writers <= 0 || cycles <= 0 ||
        num_readers > MAX || num_writers > MAX) {
        printf("Invalid input.\n");
        return 1;
    }

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&wrt, NULL);

    // Create reader threads
    for (int i = 0; i < num_readers; i++) {
        r_ids[i] = i;
        pthread_create(&r_threads[i], NULL, reader, &r_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < num_writers; i++) {
        w_ids[i] = i;
        pthread_create(&w_threads[i], NULL, writer, &w_ids[i]);
    }

    // Join threads
    for (int i = 0; i < num_readers; i++) {
        pthread_join(r_threads[i], NULL);
    }

    for (int i = 0; i < num_writers; i++) {
        pthread_join(w_threads[i], NULL);
    }

    printf("\nSimulation Completed Successfully.\n");

    fclose(logFile);

    return 0;
}