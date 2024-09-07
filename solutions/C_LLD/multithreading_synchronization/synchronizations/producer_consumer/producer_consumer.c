#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10

// Shared buffer and its associated variables
int buffer[BUFFER_SIZE];
int in = 0;  // Index for producer
int out = 0; // Index for consumer

// Semaphores and mutexes
sem_t empty;  // Semaphore to count empty slots
sem_t full;   // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for mutual exclusion

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item (random number for demonstration)

        // Wait for empty slot
        sem_wait(&empty);

        // Lock the mutex for exclusive access to the buffer
        pthread_mutex_lock(&mutex);

        // Add item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);

        // Unlock the mutex and signal that there is a new full slot
        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        // Simulate some processing time
        sleep(rand() % 3);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        // Wait for a full slot
        sem_wait(&full);

        // Lock the mutex for exclusive access to the buffer
        pthread_mutex_lock(&mutex);

        // Remove item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);

        // Unlock the mutex and signal that there is a new empty slot
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);

        // Simulate some processing time
        sleep(rand() % 3);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, BUFFER_SIZE); // Start with BUFFER_SIZE empty slots
    sem_init(&full, 0, 0); // Start with 0 full slots
    pthread_mutex_init(&mutex, NULL);

    // Create producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish (they won't in this infinite loop example)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Cleanup
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
