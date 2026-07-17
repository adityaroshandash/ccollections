#include <stdlib.h>
#include "list.h"

/**
 * @brief The internal structural unit handling the generic value payload.
 */
typedef struct ListNode {
    void *element;              // Universal void pointer payload
    struct ListNode *next;      // Pointer to the successive node
    struct ListNode *prev;      // Pointer to the preceding node
} ListNode;

/**
 * @brief Private tracking layout hidden inside the collection_context pointer.
 */
typedef struct LinkedListInternal {
    ListNode *head;             // Reference pointer to the origin boundary node
    ListNode *tail;             // Reference pointer to the final boundary node
    size_t size;                // Tracks element count to avoid O(N) traversal on size checks
} LinkedListInternal;
// Size tracker lookup override
static size_t linkedlist_size(const Collection *self) {
    LinkedListInternal *internal = (LinkedListInternal*)self->collection_context;
    return internal->size;
}

// Node traversal utility helper (internal only)
static ListNode* get_node_at(LinkedListInternal *internal, size_t index) {
    if (index >= internal->size) return NULL;
    
    // Optimization step: Decide whether to search from Head or Tail
    ListNode *current;
    if (index < internal->size / 2) {
        current = internal->head;
        for (size_t i = 0; i < index; i++) current = current->next;
    } else {
        current = internal->tail;
        for (size_t i = internal->size - 1; i > index; i--) current = current->prev;
    }
    return current;
}

// Concrete List implementation of positional retrieval
static void* linkedlist_get(const List *self, size_t index) {
    LinkedListInternal *internal = (LinkedListInternal*)self->collection.collection_context;
    ListNode *node = get_node_at(internal, index);
    return node ? node->element : NULL;
}

// Concrete Collection implementation of adding an element (Appends to Tail)
static bool linkedlist_add(Collection *self, void *element) {
    LinkedListInternal *internal = (LinkedListInternal*)self->collection_context;
    
    ListNode *new_node = malloc(sizeof(ListNode));
    if (!new_node) return false;
    
    new_node->element = element;
    new_node->next = NULL;
    new_node->prev = internal->tail;
    
    if (!internal->head) {
        internal->head = new_node; // List was empty
    } else {
        internal->tail->next = new_node;
    }
    
    internal->tail = new_node;
    internal->size++;
    return true;
}
/**
 * @brief Instantiates a generic List backed by a node-linked doubly structure.
 */
List* create_linkedlist(void) {
    List *list_interface = malloc(sizeof(List));
    LinkedListInternal *internal = malloc(sizeof(LinkedListInternal));
    
    if (!list_interface || !internal) {
        free(list_interface);
        free(internal);
        return NULL;
    }

    // 1. Initialize underlying pointers
    internal->head = NULL;
    internal->tail = NULL;
    internal->size = 0;

    // 2. Bind the underlying context boundary
    list_interface->collection.collection_context = internal;

    // 3. Bind standard Collection behaviors
    list_interface->collection.size = linkedlist_size;
    list_interface->collection.add = linkedlist_add;
    // (Bind remove, clear, and iterable functionality here...)

    // 4. Bind specific List positional overrides
    list_interface->get = linkedlist_get;
    // (Bind set, insert_at, remove_at overrides here...)

    return list_interface;
}