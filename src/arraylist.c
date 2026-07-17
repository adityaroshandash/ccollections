#include <stdlib.h>
#include <string.h>
#include "list.h"

#define ARRAYLIST_INITIAL_CAPACITY 10

/**
 * @brief Private tracking layout hidden inside the collection_context pointer.
 */
typedef struct ArrayListInternal {
    void **elements;      // Contiguous array of raw void pointers
    size_t capacity;      // Total capacity slots currently allocated
    size_t size;          // Count of occupied slots
} ArrayListInternal;

// Forward declaration of the sizing function mapping to Collection
static size_t arraylist_size(const Collection *self) {
    ArrayListInternal *internal = (ArrayListInternal*)self->collection_context;
    return internal->size;
}

// Internal array growth checker
static bool arraylist_ensure_capacity(ArrayListInternal *internal) {
    if (internal->size >= internal->capacity) {
        size_t new_capacity = internal->capacity * 2;
        void **new_elements = realloc(internal->elements, sizeof(void*) * new_capacity);
        if (!new_elements) return false;
        
        internal->elements = new_elements;
        internal->capacity = new_capacity;
    }
    return true;
}

// Concrete List implementation of positional retrieval
static void* arraylist_get(const List *self, size_t index) {
    ArrayListInternal *internal = (ArrayListInternal*)self->collection.collection_context;
    if (index >= internal->size) return NULL;
    return internal->elements[index];
}

// Concrete Collection implementation of appending an element
static bool arraylist_add(Collection *self, void *element) {
    ArrayListInternal *internal = (ArrayListInternal*)self->collection_context;
    if (!arraylist_ensure_capacity(internal)) return false;
    
    internal->elements[internal->size] = element;
    internal->size++;
    return true;
}
/**
 * @brief Instantiates a generic List backed by a dynamic array structure.
 */
List* create_arraylist(void) {
    List *list_interface = malloc(sizeof(List));
    ArrayListInternal *internal = malloc(sizeof(ArrayListInternal));
    
    if (!list_interface || !internal) {
        free(list_interface);
        free(internal);
        return NULL;
    }

    // 1. Initialize underlying dynamic storage state
    internal->elements = malloc(sizeof(void*) * ARRAYLIST_INITIAL_CAPACITY);
    internal->capacity = ARRAYLIST_INITIAL_CAPACITY;
    internal->size = 0;

    // 2. Bind the underlying context
    list_interface->collection.collection_context = internal;

    // 3. Bind standard Collection behaviors
    list_interface->collection.size = arraylist_size;
    list_interface->collection.add = arraylist_add;
    // (Remaining functions like remove, clear, and iterable bind here...)

    // 4. Bind specific List interface extensions
    list_interface->get = arraylist_get;
    // (Remaining functions like set, insert_at, remove_at bind here...)

    return list_interface;
}