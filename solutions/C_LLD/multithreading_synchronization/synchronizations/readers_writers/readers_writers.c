#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_READERS 10
#define MAX_WRITERS 10

// Shared resource
int shared_data = 0;

// Semaphores and mutexes
sem_t read_mutex;        // Mutex for managing the read count
sem_t write_mutex;       // Mutex for controlling write access
sem_t resource_mutex;    // Semaphore for exclusive access to the shared resource

int read_count = 0;      // Number of active readers

// Reader thread function
void *reader(void *arg) {
    int id = *(int *)arg;

    // Request permission to read
    sem_wait(&read_mutex);
    read_count++;
    if (read_count == 1) {
        sem_wait(&resource_mutex); // First reader locks the resource
    }
    sem_post(&read_mutex);

    // Read the shared data
    printf("Reader %d: Read shared data = %d\n", id, shared_data);

    // Release permission to read
    sem_wait(&read_mutex);
    read_count--;
    if (read_count == 0) {
        sem_post(&resource_mutex); // Last reader releases the resource
    }
    sem_post(&read_mutex);

    return NULL;
}

// Writer thread function
void *writer(void *arg) {
    int id = *(int *)arg;

    // Request permission to write
    sem_wait(&write_mutex);
    sem_wait(&resource_mutex); // Lock the resource for writing

    // Write to the shared data
    shared_data += id;
    printf("Writer %d: Updated shared data to %d\n", id, shared_data);

    sem_post(&resource_mutex); // Release the resource
    sem_post(&write_mutex);

    return NULL;
}

int main() {
    pthread_t readers[MAX_READERS], writers[MAX_WRITERS];
    int reader_ids[MAX_READERS], writer_ids[MAX_WRITERS];
    int i;

    // Initialize semaphores and mutexes
    sem_init(&read_mutex, 0, 1);
    sem_init(&write_mutex, 0, 1);
    sem_init(&resource_mutex, 0, 1);

    // Create reader threads
    for (i = 0; i < MAX_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (i = 0; i < MAX_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (i = 0; i < MAX_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < MAX_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores and mutexes
    sem_destroy(&read_mutex);
    sem_destroy(&write_mutex);
    sem_destroy(&resource_mutex);

    return 0;
}
