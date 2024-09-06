# Circular Data Structures

## Circular Queue Implementation in C

### Description:
A **circular queue** is a data structure where the last position is connected back to the first position, creating a circular arrangement. This data structure is widely used to manage bounded buffers, cyclic access patterns, and resources with limited capacity. Circular queues efficiently reuse available space, unlike linear queues that may leave unused spaces after dequeuing elements.

### Key Concepts:
- **Circular Buffers**: The array is used as a circular buffer where positions wrap around when they reach the end, allowing efficient use of storage.
- **Pointers**: `front` and `rear` pointers are used to manage the insertion (enqueue) and removal (dequeue) operations in the queue.
- **Queue Management**: Efficiently manage insertion and deletion of elements in a fixed-size queue with the ability to reuse space in a circular manner.

### Fundamentals for Implementation:
1. **Array Representation**: The queue is represented by a fixed-size array. The `front` pointer tracks the element to be dequeued, and the `rear` pointer tracks where the next element will be enqueued.
2. **Circular Increment**: Both the `front` and `rear` pointers move circularly. When either reaches the end of the array, they wrap around to the beginning using the formula:

**new_index = (current_index + 1) % SIZE;**

This formula ensures that the index wraps around to the start when it exceeds the array bounds.
3. **Queue Full/Empty Conditions**:
- The queue is **empty** when both `front` and `rear` pointers are `-1`.
- The queue is **full** when the `rear` pointer is one position behind the `front` pointer in a circular manner.

### Scenarios Where Circular Queues are Used:
1. **Bounded Buffers**: Circular queues are used in situations where the buffer size is fixed, such as in **network routers** where data packets are processed in a cyclic order.
2. **Operating Systems**: Task scheduling often uses circular queues to cycle through processes waiting for CPU time.
3. **Streaming Data**: Audio or video streaming applications use circular buffers to maintain a continuous stream of data, even as data is being read and written simultaneously.

## Explanation of Code:

### Initialization:
The queue is initialized with both `front` and `rear` pointers set to `-1`.

### Enqueue:
Adds an element to the queue if it's not full. If the queue is empty, both `front` and `rear` pointers are set to `0`. Otherwise, the `rear` pointer is updated using the circular increment formula.

### Dequeue:
Removes an element from the front if the queue is not empty. If the queue has only one element left, both pointers are reset to `-1`. Otherwise, the `front` pointer is updated using the circular increment formula.

### Display:
Prints the queue elements in the correct order, handling both cases where the `rear` pointer is ahead or behind the `front` pointer due to circular wrapping.

## Use Cases of Circular Queue:

### Producer-Consumer Problems:
Circular queues are widely used in producer-consumer models where a fixed buffer is shared between processes.

### Handling Circular Buffers:
In systems where memory buffers are limited, circular buffers are used to manage the data continuously without overwriting unread data.
