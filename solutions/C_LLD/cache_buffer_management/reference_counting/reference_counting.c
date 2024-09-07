#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;            // Pointer to the actual data
    int ref_count;        // Reference count for this object
} RefCountedObject;

// Function to create a new reference-counted object
RefCountedObject* createObject(int value) {
    RefCountedObject *obj = (RefCountedObject *)malloc(sizeof(RefCountedObject));
    obj->data = (int *)malloc(sizeof(int));
    *(obj->data) = value;
    obj->ref_count = 1;  // Initially, the reference count is 1
    return obj;
}

// Function to increase the reference count
void retainObject(RefCountedObject *obj) {
    if (obj) {
        obj->ref_count++;
        printf("Object retained, new ref_count: %d\n", obj->ref_count);
    }
}

// Function to decrease the reference count and free memory when necessary
void releaseObject(RefCountedObject *obj) {
    if (obj) {
        obj->ref_count--;
        printf("Object released, new ref_count: %d\n", obj->ref_count);
        if (obj->ref_count == 0) {
            free(obj->data);
            free(obj);
            printf("Object freed.\n");
        }
    }
}

// Function to get the current value of the object
int getObjectValue(RefCountedObject *obj) {
    if (obj && obj->data) {
        return *(obj->data);
    }
    return 0;  // Return 0 if object is NULL or data is NULL
}

int main() {
    // Create a new reference-counted object
    RefCountedObject *obj1 = createObject(42);
    printf("Object created with value: %d\n", getObjectValue(obj1));

    // Retain the object (increase reference count)
    retainObject(obj1);

    // Simulate another reference to the object
    RefCountedObject *obj2 = obj1;
    retainObject(obj2);  // Increase reference count again

    // Release the object twice
    releaseObject(obj1);  // Decrease reference count
    releaseObject(obj2);  // Decrease reference count, should free memory now

    return 0;
}
