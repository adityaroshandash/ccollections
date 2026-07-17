#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>

/**
 * @brief The active tracking cursor structure.
 */
typedef struct Iterator {
    void *internal_state;  // Tracks current iteration index or node reference safely hidden from the caller
    void *collection_ref;  // Reference back to the parent collection to cross-check constraints
    
    /**
     * @brief Determines whether the collection contains more valid elements.
     * @return true if an element exists, false otherwise.
     */
    bool (*has_next)(struct Iterator *self);

    /**
     * @brief Retrieves the current element pointer and advances the tracking position.
     * @return A void pointer to the payload data element.
     */
    void* (*next)(struct Iterator *self);
} Iterator;

/**
 * @brief Behavioral interface applied to collections enabling Iterator acquisition.
 */
typedef struct Iterable {
    /**
     * @brief Instantiates and returns an active iterator configuration for the target collection.
     */
    Iterator (*iterator)(void *collection);
} Iterable;

#endif // ITERATOR_H