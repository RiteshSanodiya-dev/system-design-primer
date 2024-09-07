#### Reference Counting

**Description:** Implement reference counting to manage object lifetimes in manual memory management.

**Key Concepts:**

- **Memory Management:** Refers to the process of allocating and freeing memory in a system. Effective memory management is crucial to avoid memory leaks and ensure that memory is used efficiently.
- **Object Lifetime:** The period during which an object is in use and should remain allocated in memory. Reference counting helps track this lifetime based on how many references are pointing to the object.
- **Reference Handling:** This involves managing how references to an object are created and destroyed. Reference counting maintains a count of active references and automatically frees the object's memory when the reference count drops to zero.

#### Benefits and Applications

1. **Automatic Memory Management:** Reference counting automates memory management by tracking how many references exist to an object. When there are no more references, the object’s memory is automatically freed. This helps prevent memory leaks, where memory is not released even though it is no longer needed.

2. **Efficient Resource Utilization:** By managing memory dynamically and deallocating objects when they are no longer in use, reference counting ensures that memory resources are used efficiently, reducing the risk of running out of memory.

3. **Avoiding Dangling Pointers:** Reference counting helps prevent dangling pointers, which occur when a pointer still references a memory location after it has been freed. By ensuring that memory is only freed when no references exist, reference counting helps avoid this problem.

4. **Simpler Memory Management:** This technique can simplify memory management in complex systems by removing the need for manual deallocation of objects. This is particularly useful in scenarios where objects are shared across different parts of a system.

#### Typical Use Cases

1. **Garbage Collection Systems:** Reference counting is often used in garbage collectors to manage memory in programming languages that do not have automatic garbage collection, such as C and C++.

2. **Resource Management:** In systems where resources (e.g., file handles, network connections) need to be managed carefully, reference counting can track how many parts of the system are using a resource and release it when it is no longer in use.

3. **Smart Pointers:** In modern C++ programming, smart pointers (e.g., `std::shared_ptr`) use reference counting to manage the lifetime of objects, making it easier to handle memory management and avoid common pitfalls like double-free errors.

#### Objective

The primary goal of implementing reference counting is to ensure robust and efficient memory management by automatically handling object lifetimes. This helps developers avoid common memory management issues and simplifies the process of managing dynamically allocated memory.

### Implimentation Explanation:

- **RefCountedObject**: A structure containing a pointer to the data (`int *data`) and a `ref_count` to manage how many references are pointing to this object.

- **createObject**: Allocates memory for a new object and initializes it with a given value, setting the reference count to 1.

- **retainObject**: Increases the reference count when a new reference is made to the object.

- **releaseObject**: Decreases the reference count, and when it reaches zero, the memory is freed.

- **getObjectValue**: Retrieves the current value stored in the object.
