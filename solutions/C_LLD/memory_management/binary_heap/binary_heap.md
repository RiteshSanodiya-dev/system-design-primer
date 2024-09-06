# Heap Implementation for Memory Management

## Problem Description

A **binary heap** is a complete binary tree that satisfies the heap property:
- In a **min-heap**, for any given node, the value of the node is less than or equal to the values of its children.
- In a **max-heap**, for any given node, the value of the node is greater than or equal to the values of its children.

The heap is primarily used in memory management for efficient priority queue operations such as insertion, deletion, and extracting the minimum or maximum element in constant time. This is particularly important for managing dynamic memory allocation.

### Key Concepts:
- **Binary Tree**: A tree data structure where each node has at most two children (left and right).
- **Heap Operations**: Inserting a new element, deleting the root, heapifying up or down.
- **Sorting**: Maintaining the heap property, which ensures the structure remains valid as elements are inserted or removed.

### Key Points:
1. **Complete Binary Tree**: The heap is a complete binary tree, meaning all levels are filled except possibly the last level, which is filled from left to right.
2. **Heap Property**: 
   - In a **min-heap**, for every node `i`:  
     `arr[i] <= arr[2*i + 1]` and `arr[i] <= arr[2*i + 2]`
   - In a **max-heap**, the inequality is reversed.

### Formula for Accessing Elements in a Heap

When a binary heap is stored in an array:
- **Parent of a node** at index `i`: `parent(i) = (i - 1) / 2`
- **Left child of a node** at index `i`: `left(i) = 2*i + 1`
- **Right child of a node** at index `i`: `right(i) = 2*i + 2`

## Solution Explanation

This solution implements a binary heap in C to manage memory efficiently. The heap supports both min-heaps and max-heaps, making it versatile for different use cases. The key operations supported by the heap are:
1. **Insertion of an element**.
2. **Deletion of the root element**.
3. **Heapify operation** to maintain the heap property after any modification.

### Data Structure

We use a struct `Heap` to represent the heap. It contains:
- `arr`: An array to store the heap elements.
- `count`: The number of elements in the heap.
- `capacity`: The maximum capacity of the heap.
- `heap_type`: A flag that determines if the heap is a min-heap (`MIN_HEAP = 0`) or a max-heap (`MAX_HEAP = 1`).

### Functions in the Solution

1. **createHeap()**: Initializes a heap with a given capacity and type (min or max).
2. **parent()**: Returns the index of the parent of a given node.
3. **leftChild()**: Returns the index of the left child of a given node.
4. **rightChild()**: Returns the index of the right child of a given node.
5. **insert()**: Inserts a new element into the heap and adjusts the position using the heapify-up operation based on whether it's a min-heap or max-heap.
6. **heapify()**: A recursive function to maintain the heap property after an element is removed from the root. It compares the parent with its children and swaps if necessary.
7. **extract()**: Removes and returns the root element (minimum for min-heap, maximum for max-heap). After removal, the heapify-down operation is used to restore the heap property.
8. **displayHeap()**: A utility function to print the current state of the heap.

### Detailed Steps of Operations

1. **Insertion**:
   - When a new element is inserted, it is added to the end of the array.
   - Then, the heapify-up operation is performed, where the inserted element is compared with its parent and swapped if it violates the heap property.
   - This operation continues until the heap property is restored or the element becomes the root.

2. **Deletion (Extract)**:
   - The root element is removed, and the last element is moved to the root.
   - The heapify-down operation is performed, where the new root is compared with its children.
   - It is swapped with the smaller child in the case of a min-heap (or larger child for a max-heap) to restore the heap property.
   - This operation continues until the heap property is satisfied.

3. **Heapify**:
   - The heapify function is a recursive operation that ensures the heap property is maintained. It starts from a given node, compares it with its children, and makes the necessary swaps.

### Example

Let's consider inserting elements into a **min-heap**. Initially, the heap is empty. After inserting elements `10, 20, 5, 3, 7`, the heap looks like:


```
         3
       /   \
     7       5
   /  \
 10    20
 ```



- The root is the smallest element `3`, and all other elements are arranged in a way that satisfies the min-heap property.

Now, if we remove the root `3`, the heap is reorganized:

```
         5
       /   \
     7      20
   /
 10
 ```

- The new root is `5`, and the heapify-down operation ensures the heap property is maintained.
