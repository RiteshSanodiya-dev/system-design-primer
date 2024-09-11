#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node* next;
    struct node* prev;
} node_t;

typedef struct deque {
    node_t* front;
    node_t* rear;
} deque_t;

node_t* create_node(int data)
{
    node_t* newNode = (node_t*)malloc(sizeof(node_t));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

deque_t* initialize_deque()
{
    deque_t* dq = (deque_t*) malloc(sizeof(deque_t));
    dq->front = NULL;
    dq->rear = NULL;
    return dq;
}

bool is_empty(deque_t* dq)
{
    if(dq->front == NULL)
        return true;
    else
        return false;
}

void insert_front(deque_t* dq, int data)
{
    node_t* newNode = create_node(data);

    if (is_empty(dq)) {
        dq->front = dq->rear = newNode;
        newNode->prev = newNode->next = NULL; // Initialize both pointers if no nodes are present
    } else {
        newNode->next = dq->front;
        newNode->prev = NULL; // The new node is now the first node, so prev is NULL
        dq->front->prev = newNode; // Link the current front node back to the new node
        dq->front = newNode; // Update the front pointer to point to the new node
    }
    printf("inserted [%d] at front\n", data);
}

void insert_rear(deque_t* dq, int data)
{
    node_t* newNode = (node_t*) malloc(sizeof(node_t));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return; // Handle memory allocation failure
    }

    newNode->data = data; // Assuming node_t has a data field
    newNode->next = NULL; // Initialize next pointer
    newNode->prev = NULL; // Initialize prev pointer

    if (is_empty(dq)) {
        dq->front = dq->rear = newNode;
    } else {
        newNode->prev = dq->rear;
        dq->rear->next = newNode;
        dq->rear = newNode;
    }
    printf("inserted [%d] at rear\n", data);
}

void delete_front(deque_t* dq)
{
    if(is_empty(dq)) {
        printf("deque is empty, cannot delete from front\n");
        return;
    } else {
        printf("deleting element [%d] from front\n", dq->front->data);
        node_t* tmp = dq->front;
        dq->front = tmp->next;
        if (dq->front != NULL) {
            dq->front->prev = NULL; // Update new front's previous pointer
        } else {
            dq->rear = NULL;
        }
        free(tmp);
    }
}

void delete_rear(deque_t* dq)
{
    if(is_empty(dq)) {
        printf("deque is empty, cannot delete from rear\n");
        return;
    } else {
        printf("deleting element [%d] from rear\n", dq->rear->data);
        node_t* tmp = dq->rear;
        dq->rear = tmp->prev;
        if(dq->rear != NULL) { 
            dq->rear->next = NULL;
        } else {
            dq->front = NULL;
        }
        free(tmp);
    }
}

int get_front(deque_t* dq)
{
    if (dq == NULL) {
        printf("deque is NULL\n");
        return -1; // or handle the error appropriately
    }

    if (is_empty(dq)) {
        printf("deque is empty\n");
        return -1;
    }

    return dq->front->data; 
}

int get_rear(deque_t* dq)
{
    if (dq == NULL) {
        printf("deque is NULL\n");
        return -1; // or handle the error appropriately
    }

    if (is_empty(dq)) {
        printf("deque is empty\n");
        return -1;
    }

    return dq->rear->data; 
}

int main()
{
    deque_t* dq = initialize_deque();

    insert_front(dq, 10);
    insert_rear(dq, 20);
    insert_front(dq, 5);
    insert_rear(dq, 25);

    printf("Front element: %d\n", get_front(dq));
    printf("Rear element: %d\n", get_rear(dq));

    delete_front(dq);
    delete_rear(dq);

    printf("Front element after deletion: %d\n", get_front(dq));
    printf("Rear element after deletion: %d\n", get_rear(dq));

    return 0;
}
