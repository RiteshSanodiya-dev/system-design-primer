## Explanation

### Data Structures:

- **`sem_t read_mutex`**: A semaphore to manage access to the `read_count` variable.
- **`sem_t write_mutex`**: A semaphore to control exclusive access for writing.
- **`sem_t resource_mutex`**: A semaphore to manage exclusive access to the shared resource.

### Reader Function:

- Uses `read_mutex` to manage the number of readers.
- The first reader locks the resource using `resource_mutex`, and the last reader releases it.

### Writer Function:

- Uses `write_mutex` to ensure exclusive write access.
- Acquires `resource_mutex` before writing to the shared resource and releases it afterward.

### Main Function:

- Initializes semaphores and mutexes.
- Creates and manages multiple reader and writer threads.
- Waits for all threads to complete before cleaning up and destroying semaphores.

This code handles the synchronization between multiple readers and writers, ensuring that readers can access the shared resource
concurrently while writers have exclusive access.
