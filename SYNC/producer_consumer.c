#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

FILE *logFile;

int buffer[MAX];
int in = 0, out = 0;
int count = 0;

int size;
int num_producers, num_consumers, cycles;

pthread_mutex_t mutex;
pthread_cond_t not_full;
pthread_cond_t not_empty;


// -------- PRODUCER --------
void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < cycles; i++) {

        int item = rand() % 100;

        pthread_mutex_lock(&mutex);

        while (count == size)
            pthread_cond_wait(&not_full, &mutex);

        buffer[in] = item;
        printf("Producer %d produced: %d\n", id, item);

        in = (in + 1) % size;
        count++;

        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}


// -------- CONSUMER --------
void* consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < cycles; i++) {

        pthread_mutex_lock(&mutex);

        while (count == 0)
            pthread_cond_wait(&not_empty, &mutex);

        int item = buffer[out];
        printf("Consumer %d consumed: %d\n", id, item);

        out = (out + 1) % size;
        count--;

        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);

        sleep(1);
    }

    return NULL;
}


int main() {

    pthread_t p_threads[MAX], c_threads[MAX];
    int p_ids[MAX], c_ids[MAX];

    // -------- USER INPUT --------
    printf("Enter buffer size: ");
    scanf("%d", &size);

    printf("Enter number of producers: ");
    scanf("%d", &num_producers);

    printf("Enter number of consumers: ");
    scanf("%d", &num_consumers);

    printf("Enter number of cycles: ");
    scanf("%d", &cycles);

    if (size <= 0 || size > MAX ||
        num_producers <= 0 || num_producers > MAX ||
        num_consumers <= 0 || num_consumers > MAX ||
        cycles <= 0) {

        printf("Invalid input.\n");
        return 1;
    }

    // Initialize
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&not_full, NULL);
    pthread_cond_init(&not_empty, NULL);

    // Create producers
    for (int i = 0; i < num_producers; i++) {
        p_ids[i] = i;
        pthread_create(&p_threads[i], NULL, producer, &p_ids[i]);
    }

    // Create consumers
    for (int i = 0; i < num_consumers; i++) {
        c_ids[i] = i;
        pthread_create(&c_threads[i], NULL, consumer, &c_ids[i]);
    }

    // Join threads
    for (int i = 0; i < num_producers; i++) {
        pthread_join(p_threads[i], NULL);
    }

    for (int i = 0; i < num_consumers; i++) {
        pthread_join(c_threads[i], NULL);
    }

    printf("\nSimulation Completed Successfully.\n");

    return 0;
}