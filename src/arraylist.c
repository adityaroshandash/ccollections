#include <stdlib.h>
#include <string.h>
#include <stdbool.h>  // FIX: Defines bool, true, and false
#include <stdio.h>
#include "list.h"     // FIX: Bridges the List and Collection struct definitions

/**
 * @brief Private tracking layout hidden inside the collection_context pointer.
 */
typedef struct ArrayListInternal {
    void **elements;      // Contiguous array of raw void pointers
    size_t capacity;      // Total capacity slots currently allocated
    size_t size;          // Count of occupied slots
} ArrayListInternal;

#define ARRAYLIST_INITIAL_CAPACITY 10

// --- 1. Internal Sizing & Capacity Management ---

static size_t arraylist_size(const Collection *self) {
    if (!self || !self->collection_context) return 0;
    ArrayListInternal *internal = (ArrayListInternal*)self->collection_context;
    return internal->size;
}

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

// --- 2. Core Collection Implementation Functions ---

static bool arraylist_add(Collection *self, void *element) {
    if (!self || !self->collection_context) return false;
    ArrayListInternal *internal = (ArrayListInternal*)self->collection_context;
    
    if (!arraylist_ensure_capacity(internal)) return false;
    
    internal->elements[internal->size] = element;
    internal->size++;
    return true;
}

// Stub implementations to fulfill the Collection contract interface assignments
static bool arraylist_remove(Collection *self, void *element, CompareFunc comp, FreeFunc free_elem) {
    (void)self; (void)element; (void)comp; (void)free_elem;
    return false; // To be completed in Week 4/5 roadmap
}

static bool arraylist_contains(const Collection *self, const void *element, CompareFunc comp) {
    (void)self; (void)element; (void)comp;
    return false;
}

static void arraylist_clear(Collection *self, FreeFunc free_elem) {
    if (!self || !self->collection_context) return;
    ArrayListInternal *internal = (ArrayListInternal*)self->collection_context;
    if (free_elem) {
        for (size_t i = 0; i < internal->size; i++) {
            free_elem(internal->elements[i]);
        }
    }
    internal->size = 0;
}

// --- 3. Positional List Extensions ---

static void* arraylist_get(const List *self, size_t index) {
    if (!self || !self->collection.collection_context) return NULL;
    ArrayListInternal *internal = (ArrayListInternal*)self->collection.collection_context;
    if (index >= internal->size) return NULL;
    return internal->elements[index];
}

static void* arraylist_set(List *self, size_t index, void *element) {
    (void)self; (void)index; (void)element;
    return NULL;
}

static bool arraylist_insert_at(List *self, size_t index, void *element) {
    (void)self; (void)index; (void)element;
    return false;
}

static void* arraylist_remove_at(List *self, size_t index) {
    (void)self; (void)index;
    return NULL;
}

// --- 4. The Factory Instantiator ---

List* create_arraylist(void) {
    List *list_interface = malloc(sizeof(List));
    ArrayListInternal *internal = malloc(sizeof(ArrayListInternal));
    
    if (!list_interface || !internal) {
        free(list_interface);
        free(internal);
        return NULL;
    }

    // Initialize underlying dynamic storage state
    internal->elements = malloc(sizeof(void*) * ARRAYLIST_INITIAL_CAPACITY);
    if (!internal->elements) {
        free(internal);
        free(list_interface);
        return NULL;
    }
    internal->capacity = ARRAYLIST_INITIAL_CAPACITY;
    internal->size = 0;

    // Bind the underlying context boundary
    list_interface->collection.collection_context = internal;

    // Bind standard Collection behaviors
    list_interface->collection.size = arraylist_size;
    list_interface->collection.add = arraylist_add;
    list_interface->collection.remove = arraylist_remove;
    list_interface->collection.contains = arraylist_contains;
    list_interface->collection.clear = arraylist_clear;
    
    // Base iterable contract mapping placeholder
    list_interface->collection.iterable.iterator = NULL; 

    // Bind specific List interface extensions
    list_interface->get = arraylist_get;
    list_interface->set = arraylist_set;
    list_interface->insert_at = arraylist_insert_at;
    list_interface->remove_at = arraylist_remove_at;

    return list_interface;
}
