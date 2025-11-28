#ifndef CSTACK_H
#define CSTACK_H

#include <stddef.h>
#include <stdbool.h>

struct CVector;

struct CStack {
    struct CVector *data;
};

struct CStack *cstack_create();

void cstack_free(struct CStack *stack);

void cstack_push(struct CStack *stack, void *item);

void *cstack_pop(struct CStack *stack);

void *cstack_peek(struct CStack *stack);

bool cstack_is_empty(struct CStack *stack);

size_t cstack_size(struct CStack *stack);

#endif
