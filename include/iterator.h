#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>

typedef struct Iterator {
    void *internal_state;
    void *collection_ref;
    bool (*has_next)(struct Iterator *self);
    void* (*next)(struct Iterator *self);
} Iterator;

typedef struct Iterable {
    Iterator (*iterator)(void *collection);
} Iterable;

#endif // ITERATOR_H
