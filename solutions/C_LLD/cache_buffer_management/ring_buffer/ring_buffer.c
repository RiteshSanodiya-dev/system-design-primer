#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 5  // Define the size of the circular buffer

typedef struct {
    int buffer[BUFFER_SIZE];  // The circular buffer array
    int head;  // Points to the next position to write
    int tail;  // Points to the next position to read
    int size;  // Current size of the buffer
} CircularBuffer;

// Function to initialize the circular buffer
void initializeBuffer(CircularBuffer* cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->size = 0;
}

// Function to check if the buffer is full
int isFull(CircularBuffer* cb) {
    return cb->size == BUFFER_SIZE;
}

// Function to check if the buffer is empty
int isEmpty(CircularBuffer* cb) {
    return cb->size == 0;
}

// Function to add an element to the circular buffer
void writeBuffer(CircularBuffer* cb, int item) {
    if (isFull(cb)) {
        printf("Buffer is full. Overwriting the oldest data.\n");
        cb->tail = (cb->tail + 1) % BUFFER_SIZE;  // Move tail to next position
    } else {
        cb->size++;  // Increment the size of the buffer
    }
    
    cb->buffer[cb->head] = item;  // Write item to buffer
    cb->head = (cb->head + 1) % BUFFER_SIZE;  // Move head to next position
}

// Function to read an element from the circular buffer
int readBuffer(CircularBuffer* cb) {
    if (isEmpty(cb)) {
        printf("Buffer is empty. Nothing to read.\n");
        return -1;  // Return -1 if the buffer is empty
    }
    
    int item = cb->buffer[cb->tail];  // Read the item from buffer
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;  // Move tail to next position
    cb->size--;  // Decrement the size of the buffer
    
    return item;
}

// Main function to demonstrate the circular buffer
int main() {
    CircularBuffer cb;
    initializeBuffer(&cb);

    // Writing to buffer
    writeBuffer(&cb, 10);
    writeBuffer(&cb, 20);
    writeBuffer(&cb, 30);
    writeBuffer(&cb, 40);
    writeBuffer(&cb, 50);

    // Attempt to write when buffer is full (will overwrite oldest data)
    writeBuffer(&cb, 60);

    // Reading from buffer
    printf("Read: %d\n", readBuffer(&cb));
    printf("Read: %d\n", readBuffer(&cb));

    // Writing more data
    writeBuffer(&cb, 70);
    writeBuffer(&cb, 80);

    // Reading remaining data
    while (!isEmpty(&cb)) {
        printf("Read: %d\n", readBuffer(&cb));
    }

    return 0;
}
