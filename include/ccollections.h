#ifndef CCOLLECTIONS_H
#define CCOLLECTIONS_H

#include <stddef.h>
#include <stdbool.h>
#include "iterator.h"

/**
 * @brief Free function pointer used to cleanly release generic element memory.
 * Crucial for Valgrind safety when removing elements from lists/maps.
 */
typedef void (*FreeFunc)(void *element);

/**
 * @brief Comparison function pointer.
 * Returns a negative value if element1 < element2,
 * zero if element1 == element2,
 * or a positive value if element1 > element2.
 */
typedef int (*CompareFunc)(const void *element1, const void *element2);

/**
 * @brief The base Collection interface blueprint.
 * Incorporates Iterable to ensure all implementations can be iterated over natively.
 */
typedef struct Collection {
    /**
     * @brief Embedded Iterable interface block.
     * Mimics Java's "Collection extends Iterable" relationship.
     */
    Iterable iterable;

    /**
     * @brief Context pointer holding the actual raw internal storage instance 
     * (e.g., a pointer to ArrayList internal structure or LinkedList nodes).
     */
    void *collection_context;

    /**
     * @brief Returns the total count of elements currently tracked.
     */
    size_t (*size)(const struct Collection *self);

    /**
     * @brief Adds an element to the underlying collection context.
     * @return true if the structure mutated, false if the operation failed.
     */
    bool (*add)(struct Collection *self, void *element);

    /**
     * @brief Removes a target element matching the comparison criteria.
     * Invokes FreeFunc internally on match to assure no memory leakage.
     * @return true if successfully found and purged, false otherwise.
     */
    bool (*remove)(struct Collection *self, void *element, CompareFunc comp, FreeFunc free_elem);

    /**
     * @brief Inquires if a specified element exists in the collection.
     */
    bool (*contains)(const struct Collection *self, const void *element, CompareFunc comp);

    /**
     * @brief Purges all elements and completely resets the structural lifecycle.
     */
    void (*clear)(struct Collection *self, FreeFunc free_elem);
} Collection;

#endif // CCOLLECTIONS_H