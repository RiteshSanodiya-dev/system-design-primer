## Explanation

### Circular Buffer Structure:
- The buffer is an array of fixed size `BUFFER_SIZE`.
- The `head` points to the next write position.
- The `tail` points to the next read position.
- The `size` keeps track of how many elements are currently in the buffer.

### Write Operation:
- Data is written at the position pointed by `head`.
- If the buffer is full, the oldest data (pointed by `tail`) is overwritten, and the `tail` moves forward.

### Read Operation:
- Data is read from the position pointed by `tail`.
- The `tail` moves forward after reading an element.

### Edge Cases:
- **Full Buffer**: When the buffer is full, the oldest data is overwritten.
- **Empty Buffer**: When the buffer is empty, no read operation is allowed.
