#ifndef CCOLLECTIONS_H
#define CCOLLECTIONS_H

#include <stddef.h>
#include <stdbool.h>
#include "iterator.h"

typedef void (*FreeFunc)(void *element);
typedef int (*CompareFunc)(const void *element1, const void *element2);

typedef struct Collection {
    Iterable iterable;
    void *collection_context;
    size_t (*size)(const struct Collection *self);
    bool (*add)(struct Collection *self, void *element);
    bool (*remove)(struct Collection *self, void *element, CompareFunc comp, FreeFunc free_elem);
    bool (*contains)(const struct Collection *self, const void *element, CompareFunc comp);
    void (*clear)(struct Collection *self, FreeFunc free_elem);
} Collection;

#endif // CCOLLECTIONS_H
