#include <stdio.h>
#include <stdlib.h>

#define SIZE 5  // Define the size of the queue

// Circular Queue structure
typedef struct {
    int items[SIZE];
    int front;
    int rear;
} CircularQueue;

// Initialize the queue
void initializeQueue(CircularQueue *q) {
    q->front = -1;
    q->rear = -1;
}

// Check if the queue is full
int isFull(CircularQueue *q) {
    if ((q->front == 0 && q->rear == SIZE - 1) || (q->rear == (q->front - 1) % (SIZE - 1))) {
        return 1;
    }
    return 0;
}

// Check if the queue is empty
int isEmpty(CircularQueue *q) {
    if (q->front == -1) {
        return 1;
    }
    return 0;
}

// Add an element to the queue
void enqueue(CircularQueue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    
    if (q->front == -1) {
        // First element being inserted
        q->front = q->rear = 0;
    } else {
        // Circular increment
        q->rear = (q->rear + 1) % SIZE;
    }
    
    q->items[q->rear] = value;
    printf("Inserted %d into the queue\n", value);
}

// Remove an element from the queue
int dequeue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->items[q->front];
    if (q->front == q->rear) {
        // Queue has only one element
        q->front = q->rear = -1;
    } else {
        // Circular increment
        q->front = (q->front + 1) % SIZE;
    }

    printf("Removed %d from the queue\n", value);
    return value;
}

// Display the queue
void displayQueue(CircularQueue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue elements: ");
    if (q->rear >= q->front) {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
    } else {
        for (int i = q->front; i < SIZE; i++) {
            printf("%d ", q->items[i]);
        }
        for (int i = 0; i <= q->rear; i++) {
            printf("%d ", q->items[i]);
        }
    }
    printf("\n");
}

// Main function to demonstrate the circular queue
int main() {
    CircularQueue q;
    initializeQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);

    displayQueue(&q);

    dequeue(&q);
    dequeue(&q);

    displayQueue(&q);

    enqueue(&q, 60);
    enqueue(&q, 70);

    displayQueue(&q);

    return 0;
}
