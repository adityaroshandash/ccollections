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