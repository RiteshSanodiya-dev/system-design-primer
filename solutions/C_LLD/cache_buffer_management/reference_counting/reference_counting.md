### Explanation:

- **RefCountedObject**: A structure containing a pointer to the data (`int *data`) and a `ref_count` to manage how many references are pointing to this object.

- **createObject**: Allocates memory for a new object and initializes it with a given value, setting the reference count to 1.

- **retainObject**: Increases the reference count when a new reference is made to the object.

- **releaseObject**: Decreases the reference count, and when it reaches zero, the memory is freed.

- **getObjectValue**: Retrieves the current value stored in the object.
