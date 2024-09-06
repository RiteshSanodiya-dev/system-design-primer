# C Programming Low-Level Design (LLD) Interview Questions

## Memory Management and Data Structures

1. **LRU Cache** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Implement a Least Recently Used (LRU) cache to efficiently manage cache entries. The cache should discard the least recently used items when it exceeds its capacity.
   - **Key Concepts**: Hash maps, doubly linked lists, cache management.
   - **Solution**: [GitHub Repository](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management/LRU_cache)


2. **Heap Implementation** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Implement a binary heap for efficient priority queue management, supporting both min-heaps and max-heaps.
   - **Key Concepts**: Binary trees, heap operations, sorting.
   - **Solution**: [GitHub Repository](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management/binary_heap)

3. **Circular Data Structures** ``data_structures``
   - **Description**: Implement circular data structures like circular queues or circular linked lists to manage bounded buffers or cyclic access patterns.
   - **Key Concepts**: Circular buffers, pointers, queue management.
   - **Solution**: [GitHub Repository](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/data_structures/CircularQueue)

4. **Malloc Implementation** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Implement your own version of `malloc` and `free` for dynamic memory allocation.
   - **Key Concepts**: Memory management, heap allocation, memory fragmentation.
   - **Solution**: [GitHub Repository tbd]()

5. **Queue to Stack Conversion** ``data_structures``
   - **Description**: Convert a queue to a stack using basic queue operations.
   - **Key Concepts**: Stack and queue operations, data manipulation.
   - **Solution**: [GitHub Repository tbd]()

6. **Stack to Queue Conversion** ``data_structures``
   - **Description**: Convert a stack to a queue using basic stack operations.
   - **Key Concepts**: Queue and stack operations, data manipulation.
   - **Solution**: [GitHub Repository tbd]()

7. **Synchronization Problems** ``multithreading_synchronization``
   - **a. Readers-Writers Problem**: Design a solution for managing shared resource access between multiple readers and writers.
   - **b. Producer-Consumer Problem**: Implement a synchronization mechanism to handle a shared buffer between producers and consumers.
   - **Key Concepts**: Semaphores, mutexes, concurrency, multi-threading.
   - **Solution**: [GitHub Repository tbd]()

8. **Memory Pool Allocation** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Design a memory pool that allocates and deallocates fixed-size memory blocks to optimize memory usage.
   - **Key Concepts**: Fixed-size block allocation, memory pooling, free lists.
   - **Solution**: [GitHub Repository tbd]()

9. **Hash Map Design** ``data_structures``
   - **Description**: Design a hash map with efficient collision handling techniques like chaining or open addressing.
   - **Key Concepts**: Hashing, collision resolution, dynamic memory.
   - **Solution**: [GitHub Repository tbd]()

10. **Bit Bucket Allocator** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Design a bit bucket allocator to manage memory efficiently in fixed-size blocks.
   - **Key Concepts**: Memory allocation, bit manipulation, efficiency.
   - **Solution**: [GitHub Repository tbd]()

11. **Double-Ended Queue (Deque)** ``data_structures``
   - **Description**: Implement a deque using arrays or linked lists, supporting insertion and removal from both ends.
   - **Key Concepts**: Linked lists, dynamic arrays, deque operations.
   - **Solution**: [GitHub Repository tbd]()

12. **Ring Buffer (Circular Buffer)** ``cache_buffer_management``
   - **Description**: Implement a circular buffer with efficient reading and writing operations.
   - **Key Concepts**: Buffer management, circular structure, memory efficiency.
   - **Solution**: [GitHub Repository tbd]()

13. **Reference Counting** ``cache_buffer_management``
   - **Description**: Implement reference counting to manage object lifetimes in manual memory management.
   - **Key Concepts**: Memory management, object lifetime, reference handling.
   - **Solution**: [GitHub Repository tbd]()

14. **Custom Memory Allocator** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Design a custom memory allocator with support for `malloc`, `free`, and `realloc` functions.
   - **Key Concepts**: Dynamic memory, memory fragmentation, allocation strategies.
   - **Solution**: [GitHub Repository tbd]()

15. **Cache Simulation** ``cache_buffer_management``
   - **Description**: Simulate a cache system with different eviction policies like LRU, FIFO, etc.
   - **Key Concepts**: Cache management, eviction policies, memory access.
   - **Solution**: [GitHub Repository tbd]()

16. **Garbage Collection Algorithm** [`Memory Management`](https://github.com/RiteshSanodiya-dev/system-design-primer/tree/master/solutions/C_LLD/memory_management)
   - **Description**: Design a simple mark-and-sweep garbage collection algorithm.
   - **Key Concepts**: Memory management, garbage collection, mark-and-sweep.
   - **Solution**: [GitHub Repository tbd]()

17. **Red-Black Tree / AVL Tree** ``data_structures``
   - **Description**: Implement a self-balancing binary search tree to optimize lookup, insertion, and deletion operations.
   - **Key Concepts**: Tree balancing, binary search trees, rotations.
   - **Solution**: [GitHub Repository tbd]()

18. **Timer Wheel Implementation** ``timers``
   - **Description**: Design a timer wheel to efficiently manage and schedule multiple timers with low overhead.
   - **Key Concepts**: Circular buffers, hashing, time slots.
   - **Solution**: [GitHub Repository tbd]()

19. **High-Resolution Timer Scheduler** ``timers``
   - **Description**: Create a high-resolution timer scheduler to handle timers with microsecond precision.
   - **Key Concepts**: Priority queues, binary heaps, interrupt handling.
   - **Solution**: [GitHub Repository tbd]()

20. **Timer Queue Implementation** ``timers``
   - **Description**: Implement a timer queue to manage timers, ensuring correct order of expiration and handling simultaneous expirations.
   - **Key Concepts**: Linked lists, min-heaps, callback functions.
   - **Solution**: [GitHub Repository tbd]()

21. **Signal Handling with Timers**
   - **Description**: Implement `setitimer` and signal handling to create a timer that sends signals like `SIGALRM`.
   - **Key Concepts**: Signal handling, interrupt-driven design, system calls.
   - **Solution**: [GitHub Repository tbd]()

22. **Debounce Mechanism Using Timers** ``timers``
   - **Description**: Design a debounce mechanism to handle successive events (e.g., button presses) using timers.
   - **Key Concepts**: Event filtering, timer resets.
   - **Solution**: [GitHub Repository tbd]()

23. **Timeout Handling in Network Protocols** ``timers``
   - **Description**: Implement timeout mechanisms in network protocols (e.g., TCP retransmission) to manage retries and timeouts.
   - **Key Concepts**: Networking protocols, timeouts, state machines.
   - **Solution**: [GitHub Repository tbd]()

24. **Delayed Task Executor** ``timers``
   - **Description**: Create a delayed task executor that schedules tasks after a specified delay.
   - **Key Concepts**: Multithreading, synchronization, task scheduling.
   - **Solution**: [GitHub Repository tbd]()

25. **Rate Limiter with Token Bucket Using Timers** ``timers``
   - **Description**: Implement a rate limiter using the token bucket algorithm, where tokens are refilled at regular intervals using timers.
   - **Key Concepts**: Token bucket algorithm, rate limiting, timers.
   - **Solution**: [GitHub Repository tbd]()

26. **Periodic Task Scheduler**
   - **Description**: Design a periodic task scheduler that executes tasks at regular intervals while adjusting for drift.
   - **Key Concepts**: Scheduling, drift correction, periodic execution.
   - **Solution**: [GitHub Repository tbd]()

27. **Non-blocking Sleep Function**
   - **Description**: Implement a non-blocking sleep function using timers, allowing other tasks to execute during the sleep period.
   - **Key Concepts**: Asynchronous programming, event loops, timer callbacks.
   - **Solution**: [GitHub Repository tbd]()

28. **Alarm Management System**
   - **Description**: Develop an alarm management system where alarms can be set, modified, and triggered at specific times.
   - **Key Concepts**: Priority queues, event handling.
   - **Solution**: [GitHub Repository tbd]()

29. **Watchdog Timer** ``timers``
   - **Description**: Implement a watchdog timer that monitors system health and resets the system if it becomes unresponsive.
   - **Key Concepts**: System monitoring, reset mechanisms, timers.
   - **Solution**: [GitHub Repository tbd]()

30. **Efficient Timer Cancellation**
   - **Description**: Design an efficient mechanism to cancel active timers without performance degradation.
   - **Key Concepts**: Timer management, concurrency control.
   - **Solution**: [GitHub Repository tbd]()

31. **Timer Interrupt Simulation in Multithreaded Environment**
   - **Description**: Simulate timer interrupts in a multithreaded C program and handle timer callbacks without race conditions.
   - **Key Concepts**: Multithreading, interrupts, synchronization.
   - **Solution**: [GitHub Repository tbd]()


---

<span style="font-size: x-small; color: gray;">1: lru 2: heap 3: circular ds 4: malloc 5: queue to stack 6: stack to queue 7: timer related program
8: different synchronisation problems (readers writers, producer consumer) <br/>

memory pool implementation implementing your own memcpy design a thread pool semaphore and mutex usage in multi-threaded
applications implementing a garbage collector fixed-size block allocation (slab allocation) cache simulation atomic operations
and lock-free data structures priority queue implementation bounded buffer problem custom memory allocator with free and
realloc double buffering for concurrent read/write operations <br/>

here are some additional c-related low-level design (lld) questions, including topics you mentioned: <br/>

hash map design a hash map in c with efficient collision handling (chaining or open addressing). bit bucket allocator design
a bit allocator that efficiently manages memory in fixed-size blocks. memory pool allocation design a memory pool that allocates
and deallocates fixed-size memory blocks. custom memory allocator implement your own version of malloc and free to manage memory
manually. double-ended queue (deque) implement a deque (double-ended queue) using an array or linked list. ring buffer (circular buffer)
implement a circular buffer for data storage, including reading and writing functionality. trie (prefix tree) implement a trie data
structure to handle dynamic prefix-based searching. reference counting implement reference counting for managing object lifetimes in
manual memory management. garbage collection algorithm design a simple mark-and-sweep garbage collector. red-black tree or avl tree
implement a self-balancing binary search tree for efficient lookups.

timer-related lld interview questions implement a timer wheel description: design a timer wheel data structure to efficiently manage
and schedule multiple timers. the timer wheel should handle timer additions, cancellations, and expirations with minimal overhead.
key concepts: circular buffers, hashing, time slots, efficient lookup and insertion. high-resolution timer scheduler description:
create a high-resolution timer scheduler that can handle timers with microsecond precision. ensure that the scheduler can manage a
large number of concurrent timers without significant performance degradation. key concepts: priority queues, binary heaps, precision
timing, interrupt handling. timer queue implementation description: implement a timer queue that supports adding, removing, and executing
timers based on their expiration times. the queue should process timers in the correct order and handle edge cases like simultaneous expirations.
key concepts: linked lists, min-heaps, event-driven programming, callback functions.
...
</span>

---
