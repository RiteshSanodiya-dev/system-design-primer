## Explanation

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
