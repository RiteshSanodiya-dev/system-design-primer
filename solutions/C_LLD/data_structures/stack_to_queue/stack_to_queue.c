#include <stdio.h>
#include <stdlib.h>

// Define the structure for a stack
typedef struct Stack {
    int *arr;
    int top;
    int capacity;
} Stack;

// Define the structure for a queue
typedef struct Queue {
    int *arr;
    int front, rear, size, capacity;
} Queue;

// Function to create a stack
Stack* createStack(int capacity) {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->arr = (int*)malloc(capacity * sizeof(int));
    return stack;
}

// Function to create a queue
Queue* createQueue(int capacity) {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = -1;
    queue->size = 0;
    queue->arr = (int*)malloc(capacity * sizeof(int));
    return queue;
}

// Stack operations
int isFullStack(Stack *stack) {
    return stack->top == stack->capacity - 1;
}

int isEmptyStack(Stack *stack) {
    return stack->top == -1;
}

void push(Stack *stack, int item) {
    if (isFullStack(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = item;
}

int pop(Stack *stack) {
    if (isEmptyStack(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

int peek(Stack *stack) {
    if (isEmptyStack(stack)) {
        printf("Stack is Empty\n");
        return -1;
    }
    return stack->arr[stack->top];
}

// Queue operations
int isFullQueue(Queue *queue) {
    return queue->size == queue->capacity;
}

int isEmptyQueue(Queue *queue) {
    return queue->size == 0;
}

void enqueue(Queue *queue, int item) {
    if (isFullQueue(queue)) {
        printf("Queue Overflow\n");
        return;
    }
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->arr[queue->rear] = item;
    queue->size++;
}

int dequeue(Queue *queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue Underflow\n");
        return -1;
    }
    int item = queue->arr[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

int front(Queue *queue) {
    if (isEmptyQueue(queue)) {
        printf("Queue is Empty\n");
        return -1;
    }
    return queue->arr[queue->front];
}

// Convert stack to queue
Queue* stackToQueue(Stack *stack) {
    Queue *queue = createQueue(stack->capacity);
    Stack *tempStack = createStack(stack->capacity);

    // Transfer elements from stack to tempStack
    while (!isEmptyStack(stack)) {
        push(tempStack, pop(stack));
    }

    // Transfer elements from tempStack to queue
    while (!isEmptyStack(tempStack)) {
        enqueue(queue, pop(tempStack));
    }

    free(tempStack->arr);
    free(tempStack);
    return queue;
}

// Main function to demonstrate stack to queue conversion
int main() {
    Stack *stack = createStack(5);
    Queue *queue;

    // Push elements onto the stack
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    push(stack, 40);
    push(stack, 50);

    // Convert stack to queue
    queue = stackToQueue(stack);

    // Print queue elements
    printf("Queue elements:\n");
    while (!isEmptyQueue(queue)) {
        printf("%d\n", dequeue(queue));
    }

    // Free allocated memory
    free(stack->arr);
    free(stack);
    free(queue->arr);
    free(queue);

    return 0;
}
