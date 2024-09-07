#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure for Queue
typedef struct {
    int front, rear, size;
    int array[MAX_SIZE];
} Queue;

// Structure for Stack
typedef struct {
    Queue q1, q2;
} Stack;

// Function prototypes
void initializeQueue(Queue *q);
int isQueueEmpty(Queue *q);
int isQueueFull(Queue *q);
void enqueue(Queue *q, int item);
int dequeue(Queue *q);
int front(Queue *q);

void initializeStack(Stack *s);
int isStackEmpty(Stack *s);
void push(Stack *s, int item);
int pop(Stack *s);
int top(Stack *s);

// Initialize a queue
void initializeQueue(Queue *q) {
    q->front = q->rear = q->size = 0;
}

// Check if a queue is empty
int isQueueEmpty(Queue *q) {
    return q->size == 0;
}

// Check if a queue is full
int isQueueFull(Queue *q) {
    return q->size == MAX_SIZE;
}

// Add an item to the queue
void enqueue(Queue *q, int item) {
    if (isQueueFull(q)) {
        printf("Queue is full\n");
        return;
    }
    q->array[q->rear] = item;
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->size++;
}

// Remove an item from the queue
int dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    int item = q->array[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->size--;
    return item;
}

// Get the front item of the queue
int front(Queue *q) {
    if (isQueueEmpty(q)) {
        printf("Queue is empty\n");
        return -1;
    }
    return q->array[q->front];
}

// Initialize a stack
void initializeStack(Stack *s) {
    initializeQueue(&s->q1);
    initializeQueue(&s->q2);
}

// Check if a stack is empty
int isStackEmpty(Stack *s) {
    return isQueueEmpty(&s->q1);
}

// Push an item onto the stack
void push(Stack *s, int item) {
    if (isQueueFull(&s->q1)) {
        printf("Stack (queue) is full\n");
        return;
    }

    // Move all elements from q1 to q2
    while (!isQueueEmpty(&s->q1)) {
        enqueue(&s->q2, dequeue(&s->q1));
    }

    // Add the new item to q1
    enqueue(&s->q1, item);

    // Move all elements back from q2 to q1
    while (!isQueueEmpty(&s->q2)) {
        enqueue(&s->q1, dequeue(&s->q2));
    }
}

// Pop an item from the stack
int pop(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return dequeue(&s->q1);
}

// Get the top item of the stack
int top(Stack *s) {
    if (isStackEmpty(s)) {
        printf("Stack is empty\n");
        return -1;
    }
    return front(&s->q1);
}

// Test the stack implementation
int main() {
    Stack s;
    initializeStack(&s);

    // Push elements
    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    // Pop elements
    printf("Top of stack: %d\n", top(&s));
    printf("Popped: %d\n", pop(&s));
    printf("Top of stack after pop: %d\n", top(&s));

    return 0;
}
