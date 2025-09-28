#include "include/cvector.h"
#include <stdlib.h>
#include <stdio.h>


CVector* cvector_create() {
    CVector* vec = malloc(sizeof(CVector));
    vec->size = 0;
    vec->capacity = INITIAL_CAPACITY;
    vec->data = malloc(vec->capacity * sizeof(void*));
    return vec;
}

void cvector_free(CVector* vec) {
    free(vec->data);
    free(vec);
}

void maybe_double_capacity(CVector *vec) {
    // double the capacity if full.
    if (vec->size == vec->capacity) {
        vec->capacity *= 2;
        void** new_data = realloc(vec->data, vec->capacity);
        if (!new_data) {
            fprintf(stderr, "out of memory\n.");
            exit(1);
        }
        vec->data = new_data;
    }
}

void cvector_push(CVector *vec, void *item) {
    maybe_double_capacity(vec);
    vec->data[vec->size] = item;
    vec->size += 1;
}

void *cvector_get(CVector *vec, size_t index) {
    if (index >= vec->size) {
        return NULL;
    }
    return vec->data[index];
}


void cvector_set(CVector *vec, size_t index, void *item) {

    if (index >= vec->size) {
        return;
    }
    vec->data[index] = item;
}

void cvector_delete(CVector *vec, size_t index) {

    if (index >= vec->size) {
        return;
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



size_t cvector_size(CVector *vec) {
    return vec->size;
}