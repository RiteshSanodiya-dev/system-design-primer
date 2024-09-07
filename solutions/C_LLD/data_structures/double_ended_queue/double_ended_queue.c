#include <stdio.h>
#include <stdlib.h>

// Node structure for the deque
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Deque structure
struct Deque {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
    return newNode;
}

// Function to initialize an empty deque
struct Deque* initializeDeque() {
    struct Deque* deque = (struct Deque*)malloc(sizeof(struct Deque));
    deque->front = deque->rear = NULL;
    return deque;
}

// Function to check if deque is empty
int isEmpty(struct Deque* deque) {
    return (deque->front == NULL);
}

// Function to insert an element at the front of the deque
void insertFront(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (isEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->next = deque->front;
        deque->front->prev = newNode;
        deque->front = newNode;
    }
    printf("Inserted %d at the front\n", data);
}

// Function to insert an element at the rear of the deque
void insertRear(struct Deque* deque, int data) {
    struct Node* newNode = createNode(data);
    if (isEmpty(deque)) {
        deque->front = deque->rear = newNode;
    } else {
        newNode->prev = deque->rear;
        deque->rear->next = newNode;
        deque->rear = newNode;
    }
    printf("Inserted %d at the rear\n", data);
}

// Function to delete an element from the front of the deque
void deleteFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty. Cannot delete from front.\n");
        return;
    }

    struct Node* temp = deque->front;
    printf("Deleted %d from the front\n", temp->data);

    deque->front = deque->front->next;
    if (deque->front == NULL) {
        deque->rear = NULL;
    } else {
        deque->front->prev = NULL;
    }
    free(temp);
}

// Function to delete an element from the rear of the deque
void deleteRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty. Cannot delete from rear.\n");
        return;
    }

    struct Node* temp = deque->rear;
    printf("Deleted %d from the rear\n", temp->data);

    deque->rear = deque->rear->prev;
    if (deque->rear == NULL) {
        deque->front = NULL;
    } else {
        deque->rear->next = NULL;
    }
    free(temp);
}

// Function to get the front element of the deque
int getFront(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return -1;
    }
    return deque->front->data;
}

// Function to get the rear element of the deque
int getRear(struct Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty.\n");
        return -1;
    }
    return deque->rear->data;
}

// Main function to demonstrate deque operations
int main() {
    struct Deque* deque = initializeDeque();

    insertFront(deque, 10);
    insertRear(deque, 20);
    insertFront(deque, 5);
    insertRear(deque, 25);

    printf("Front element: %d\n", getFront(deque));
    printf("Rear element: %d\n", getRear(deque));

    deleteFront(deque);
    deleteRear(deque);

    printf("Front element after deletion: %d\n", getFront(deque));
    printf("Rear element after deletion: %d\n", getRear(deque));

    return 0;
}
