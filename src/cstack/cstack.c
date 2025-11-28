#include "cstack.h"
#include "cvector.h"

#include <stdlib.h>

struct CStack *cstack_create() {
    struct CStack *stack = malloc(sizeof(struct CStack));
    stack->data = cvector_create();
    return stack;
}

void cstack_free(struct CStack *stack) {
    cvector_free(stack->data);
    free(stack);
}

void cstack_push(struct CStack *stack, void *item) {
    cvector_push(stack->data, item);
}

void *cstack_pop(struct CStack *stack) {
    if (stack->data->size == 0) {
        return NULL;
    }
    size_t top_index = stack->data->size - 1;
    void *item = cvector_get(stack->data, top_index);
    stack->data->data[top_index] = NULL;
    stack->data->size -= 1;
    return item;
}

void *cstack_peek(struct CStack *stack) {
    if (stack->data->size == 0) {
        return NULL;
    }
    return cvector_get(stack->data, stack->data->size - 1);
}

bool cstack_is_empty(struct CStack *stack) {
    return stack->data->size == 0;
}

size_t cstack_size(struct CStack *stack) {
    return cvector_size(stack->data);
}
