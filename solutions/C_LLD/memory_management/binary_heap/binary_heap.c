#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP 1
#define MIN_HEAP 0

typedef struct {
    int *arr;
    int count;
    int capacity;
    int heap_type;  // 0 for Min-Heap, 1 for Max-Heap
} Heap;

// Function to create a heap
Heap* createHeap(int capacity, int heap_type) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap->heap_type = heap_type;
    heap->count = 0;
    heap->capacity = capacity;
    heap->arr = (int*)malloc(sizeof(int) * capacity);
    return heap;
}

// Helper functions for heap
int parent(int i) { return (i - 1) / 2; }
int leftChild(int i) { return 2 * i + 1; }
int rightChild(int i) { return 2 * i + 2; }

// Function to insert an element into the heap
void insert(Heap* heap, int key) {
    if (heap->count == heap->capacity) {
        printf("Heap is full\n");
        return;
    }
    
    heap->count++;
    int i = heap->count - 1;
    heap->arr[i] = key;
    
    // Heapify up
    if (heap->heap_type == MAX_HEAP) {
        while (i != 0 && heap->arr[parent(i)] < heap->arr[i]) {
            int temp = heap->arr[i];
            heap->arr[i] = heap->arr[parent(i)];
            heap->arr[parent(i)] = temp;
            i = parent(i);
        }
    } else {  // MIN_HEAP
        while (i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
            int temp = heap->arr[i];
            heap->arr[i] = heap->arr[parent(i)];
            heap->arr[parent(i)] = temp;
            i = parent(i);
        }
    }
}

// Function to heapify down
void heapify(Heap* heap, int i) {
    int left = leftChild(i);
    int right = rightChild(i);
    int extreme = i;
    
    if (heap->heap_type == MAX_HEAP) {
        if (left < heap->count && heap->arr[left] > heap->arr[extreme])
            extreme = left;
        if (right < heap->count && heap->arr[right] > heap->arr[extreme])
            extreme = right;
    } else {  // MIN_HEAP
        if (left < heap->count && heap->arr[left] < heap->arr[extreme])
            extreme = left;
        if (right < heap->count && heap->arr[right] < heap->arr[extreme])
            extreme = right;
    }
    
    if (extreme != i) {
        int temp = heap->arr[i];
        heap->arr[i] = heap->arr[extreme];
        heap->arr[extreme] = temp;
        heapify(heap, extreme);
    }
}

// Function to remove the root element (extract min/max)
int extract(Heap* heap) {
    if (heap->count <= 0)
        return -1;
    if (heap->count == 1) {
        heap->count--;
        return heap->arr[0];
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->count - 1];
    heap->count--;
    heapify(heap, 0);

    return root;
}

// Function to display the heap
void displayHeap(Heap* heap) {
    for (int i = 0; i < heap->count; i++)
        printf("%d ", heap->arr[i]);
    printf("\n");
}

int main() {
    // Create a min-heap with capacity 10
    Heap* minHeap = createHeap(10, MIN_HEAP);

    // Insert elements
    insert(minHeap, 10);
    insert(minHeap, 20);
    insert(minHeap, 5);
    insert(minHeap, 3);
    insert(minHeap, 7);

    // Display heap
    printf("Min-Heap: ");
    displayHeap(minHeap);

    // Extract the minimum
    printf("Extracted Min: %d\n", extract(minHeap));

    // Display heap after extraction
    printf("Min-Heap after extraction: ");
    displayHeap(minHeap);

    // Free the heap
    free(minHeap->arr);
    free(minHeap);

    return 0;
}
