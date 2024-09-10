## Double-Ended Queue (Deque)

A **Double-Ended Queue (Deque)** is a linear data structure that allows insertion and deletion of elements from both ends (front and rear). Unlike regular queues (FIFO) or stacks (LIFO), which restrict operations to one end, deques are more flexible.

## Basic Operations in a Deque:

- **Insertion at the front**: You can add elements at the front of the deque.
- **Insertion at the rear**: You can add elements at the rear of the deque.
- **Deletion from the front**: You can remove elements from the front of the deque.
- **Deletion from the rear**: You can remove elements from the rear of the deque.

### Types of Deques:

- **Input-Restricted Deque**: Insertion is allowed only at one end (either front or rear), while deletion can be done from both ends.
- **Output-Restricted Deque**: Deletion is allowed only at one end, while insertion can be done at both ends.

### Use Cases of Deques:

Deques are particularly useful in scenarios where both ends of a data structure need to be efficiently accessed and modified.

#### Sliding Window Problems:

Used in algorithms where a subset of elements is needed over a sliding window of data, like finding the maximum or minimum in all subarrays of size `k`.

- **Example**: Maximum sliding window problem in an array.

#### Palindrome Checking:

A deque can be used to efficiently check whether a string is a palindrome by comparing characters from the front and the rear.

#### Task Scheduling:

Deques are used in scheduling algorithms where tasks can be added or removed from both ends, such as multi-level queue schedulers or CPU task scheduling.

#### Undo/Redo Functionality:

A deque is often used to implement undo/redo functionality in applications, where you can push changes to the front or rear of the deque and pop them based on user actions.

#### BFS (Breadth-First Search):

Deques can be used in graph traversal (BFS) or tree traversal algorithms, as both ends of the queue might need to be accessed for adding/removing nodes.

### When Deques Are Useful:

- When you need **efficient insertion and deletion** from both ends of the data structure.
- When the access pattern alternates between the front and the rear.
- In applications with **bounded buffers**, where elements need to be processed in a cyclic manner (e.g., ring buffers, task processing systems).

### Time Complexity:

- Insertion and deletion from both ends in a deque are **O(1)** operations, which is optimal compared to a list where these operations might take **O(n)** if performed at the front.

### Diagrammatic Representation:

```python
  Front <--- [1, 2, 3, 4] ---> Rear
```

Elements can be added or removed from both the front and the rear.


## implimentation Explanation

#### Node Structure:
- Each node in the deque stores data and pointers to both the previous and next nodes, enabling bi-directional traversal.

#### Deque Structure:
- The deque has two primary pointers:
  - **Front**: Points to the front node of the deque.
  - **Rear**: Points to the rear node of the deque.

#### Insertion at Front/Rear:
- **Front**: Inserts a new node at the front of the deque, updating pointers accordingly.
- **Rear**: Inserts a new node at the rear of the deque, similarly updating pointers.

#### Deletion from Front/Rear:
- **Front**: Removes a node from the front of the deque, adjusting pointers to maintain integrity.
- **Rear**: Removes a node from the rear of the deque, ensuring pointers are correctly updated.

#### Get Front/Rear:
- **Front**: Retrieves the element at the front of the deque without removing it.
- **Rear**: Retrieves the element at the rear of the deque without removing it.



### Visualization of `insert_front` Function

Let's visualize the operations of the `insert_front` function with a diagram. We'll illustrate both scenarios: inserting into an empty deque and inserting into a non-empty deque.

### Scenario 1: Inserting into an Empty Deque

Initially, the deque is empty:

```
Deque:
+-------+
|       |  (front, rear are NULL)
+-------+
```

When we call `insert_front(deque, 10)`, the function creates a new node with the data 10. Since the deque is empty, both the front and the rear will point to this new node:


```
Deque after inserting 10:
+-------+
|   10  |  
+-------+
(front, rear -> newNode)
```

### Scenario 2: Inserting into a Non-Empty Deque

Now let's assume we already have one node in the deque, and we want to insert another value at the front. The deque currently looks like this:

```
Deque:
+-------+
|   10  |  <---- front, rear
+-------+
```

When we call `insert_front(deque, 20)`, the following steps occur:

#### Create a new node for 20:

```
   newNode: 
   +-------+
   |   20  |  
   +-------+
```

### Update the pointers in the deque:
- Set `newNode->next` to point to the current front (which contains 10):

```
    newNode->next -> +-------+
                     |   10  |
                     +-------+
```

- Update the `prev` pointer of the current front node (10) to point back to the new node (20):
``
    deque->front->prev -> +-------+
                          |   20  |
                          +-------+
``
- Update the front of the deque to point to the new node:

```
   Deque after inserting 20:
   +-------+       +-------+
   |   20  | ---> |   10  |  
   +-------+       +-------+
   (front)          (rear)
```

### Final Representation

After inserting 20, the deque is structured like this:

```
Deque:
+-------+       +-------+
|   20  |  <--> |   10  |  
+-------+       +-------+
(front)          (rear)
```

### Summary of Diagram

- In **Scenario 1**, the deque was empty and the new node became both the front and rear.
- In **Scenario 2**, the new node was added to the front, and the existing front node's pointers were updated to maintain the doubly linked structure.

### Notation

- **next**: Points to the next node in the sequence.
- **prev**: Points to the previous node in the sequence.
- The arrows (`--->`) indicate the direction of the pointers, showing how each node links to the others.

This visualization should give you a clearer understanding of how the `insert_front` function behaves in a doubly linked deque structure. If you have further questions or need more details, feel free to ask!
