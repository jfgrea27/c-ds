#include "cvector.h"
#include <stdlib.h>
#include <stdio.h>


struct CVector* cvector_create() {
    struct CVector* vec = malloc(sizeof(struct CVector));
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    vec->data = malloc(vec->capacity * sizeof(void*));
    return vec;
}

void cvector_free(struct CVector* vec) {
    for (size_t i = 0; i < vec->size; i++) {
        if (vec->data[i] != NULL) {
            free((int*)vec->data[i]);
            vec->data[i] = NULL;
        }
    }
    free(vec->data);
    free(vec);
}

void maybe_double_capacity(struct CVector *vec) {
    // double the capacity if full.
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        void** new_data = realloc(vec->data, vec->capacity * sizeof(void*));
        if (!new_data) {
            fprintf(stderr, "out of memory\n.");
            exit(1);
        }
        vec->data = new_data;
    }
}

void cvector_push(struct CVector *vec, void *item) {
    maybe_double_capacity(vec);
    vec->data[vec->size] = item;
    vec->size += 1;
}

void *cvector_get(struct CVector *vec, size_t index) {
    if (index >= vec->size) {
        return NULL;
    }
    return vec->data[index];
}


void cvector_set(struct CVector *vec, size_t index, void *item) {

    if (index >= vec->size) {
        return;
    }
    // free the old item if it exists
    if (vec->data[index] != NULL) {
        free((int*)vec->data[index]);
        vec->data[index] = NULL;
    }
    // set the new item
    vec->data[index] = item;
}

void cvector_delete(struct CVector *vec, size_t index) {

    if (index >= vec->size) {
        return;
    }
    // free the item at index
    if (vec->data[index] != NULL) {
        free((int*)vec->data[index]);
        vec->data[index] = NULL;
    }
    if (index == vec->size - 1) {
        vec->data[index] = NULL;
        vec->size -= 1;

        return;

    }
    for (size_t i = index; i <= vec->size; i ++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->size -= 1;

}



size_t cvector_size(struct CVector *vec) {
    return vec->size;
}