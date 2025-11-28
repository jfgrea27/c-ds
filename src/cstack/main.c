#include <stdio.h>
#include <stdlib.h>
#include "cstack.h"

int main() {
    struct CStack *stack = cstack_create();

    int *a = malloc(sizeof(int));
    *a = 10;
    int *b = malloc(sizeof(int));
    *b = 20;
    int *c = malloc(sizeof(int));
    *c = 30;

    cstack_push(stack, a);
    cstack_push(stack, b);
    cstack_push(stack, c);

    printf("Stack size: %zu\n", cstack_size(stack));

    int *top = cstack_pop(stack);
    printf("Popped: %d\n", *top);
    free(top);

    top = cstack_peek(stack);
    printf("Peek: %d\n", *top);

    printf("Stack size: %zu\n", cstack_size(stack));
    printf("Is empty: %s\n", cstack_is_empty(stack) ? "true" : "false");

    cstack_free(stack);

    return 0;
}
