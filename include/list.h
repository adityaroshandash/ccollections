#ifndef LIST_H
#define LIST_H

#include "ccollections.h"

typedef struct List {
    Collection collection;
    void* (*get)(const struct List *self, size_t index);
    void* (*set)(struct List *self, size_t index, void *element);         // FIX: Added 'struct'
    bool (*insert_at)(struct List *self, size_t index, void *element);   // FIX: Added 'struct'
    void* (*remove_at)(struct List *self, size_t index);                 // FIX: Added 'struct'
} List;

#endif // LIST_H
