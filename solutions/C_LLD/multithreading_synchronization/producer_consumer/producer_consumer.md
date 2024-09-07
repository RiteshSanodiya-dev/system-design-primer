# Explanation

## Shared Buffer
An array `buffer` of size `BUFFER_SIZE` is used to store items.

## Semaphores
- **`empty`**: Counts the number of empty slots in the buffer.
- **`full`**: Counts the number of full slots in the buffer.

## Mutex
- **`mutex`**: Ensures that only one thread can modify the buffer at a time.

## Producer Function
- Generates an item (a random number in this example).
- Waits for an empty slot, locks the mutex, adds the item to the buffer, unlocks the mutex, and signals that a new slot is full.

## Consumer Function
- Waits for a full slot, locks the mutex, removes an item from the buffer, unlocks the mutex, and signals that a new slot is empty.

## Main Function
- Initializes semaphores and mutex.
- Creates producer and consumer threads.
- Waits for threads to finish (in practice, this example uses infinite loops, so threads run indefinitely).
- Cleans up resources.

Feel free to adjust buffer size, sleep times, or add more producers and consumers as needed for your application.
