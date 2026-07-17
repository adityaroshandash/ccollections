#ifndef CCOLLECTIONS_H
#define CCOLLECTIONS_H

#include <stddef.h>
#include <stdbool.h>

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
 * @brief Base blueprint mimicking a Java Collection interface.
 */
typedef struct Collection {
    size_t size;
    bool (*add)(struct Collection *self, void *element);
    bool (*remove)(struct Collection *self, void *element, CompareFunc comp);
    bool (*contains)(const struct Collection *self, const void *element, CompareFunc comp);
    void (*clear)(struct Collection *self, FreeFunc free_elem);
} Collection;

#endif // CCOLLECTIONS_H