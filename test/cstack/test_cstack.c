#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cstack.h"

void test_cstack_create() {
    printf("Testing test_cstack_create\n");
    struct CStack *stack = cstack_create();

    if (stack == NULL) {
        printf("FAILED: Failed to create stack\n");
        return;
    }

    if (cstack_size(stack) != 0) {
        printf("FAILED: Stack size is not 0\n");
        return;
    }

    if (!cstack_is_empty(stack)) {
        printf("FAILED: Stack should be empty\n");
        return;
    }

    cstack_free(stack);
    printf("PASSED test_cstack_create\n");
}

void test_cstack_push() {
    printf("Testing test_cstack_push\n");
    struct CStack *stack = cstack_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");

    cstack_push(stack, str1);
    cstack_push(stack, str2);

    if (cstack_size(stack) != 2) {
        printf("FAILED: Stack size is not 2\n");
        return;
    }

    if (cstack_is_empty(stack)) {
        printf("FAILED: Stack should not be empty\n");
        return;
    }

    cstack_free(stack);
    printf("PASSED test_cstack_push\n");
}

void test_cstack_pop() {
    printf("Testing test_cstack_pop\n");
    struct CStack *stack = cstack_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");

    cstack_push(stack, str1);
    cstack_push(stack, str2);

    char *popped = cstack_pop(stack);
    if (strcmp(popped, "World") != 0) {
        printf("FAILED: Popped value is not World\n");
        return;
    }
    free(popped);

    if (cstack_size(stack) != 1) {
        printf("FAILED: Stack size is not 1\n");
        return;
    }

    popped = cstack_pop(stack);
    if (strcmp(popped, "Hello") != 0) {
        printf("FAILED: Popped value is not Hello\n");
        return;
    }
    free(popped);

    if (cstack_size(stack) != 0) {
        printf("FAILED: Stack size is not 0\n");
        return;
    }

    cstack_free(stack);
    printf("PASSED test_cstack_pop\n");
}

void test_cstack_pop_empty() {
    printf("Testing test_cstack_pop_empty\n");
    struct CStack *stack = cstack_create();

    void *popped = cstack_pop(stack);
    if (popped != NULL) {
        printf("FAILED: Pop on empty stack should return NULL\n");
        return;
    }

    cstack_free(stack);
    printf("PASSED test_cstack_pop_empty\n");
}

void test_cstack_peek() {
    printf("Testing test_cstack_peek\n");
    struct CStack *stack = cstack_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");

    cstack_push(stack, str1);
    cstack_push(stack, str2);

    char *peeked = cstack_peek(stack);
    if (strcmp(peeked, "World") != 0) {
        printf("FAILED: Peeked value is not World\n");
        return;
    }

    if (cstack_size(stack) != 2) {
        printf("FAILED: Stack size should still be 2 after peek\n");
        return;
    }

    cstack_free(stack);
    printf("PASSED test_cstack_peek\n");
}

void test_cstack_peek_empty() {
    printf("Testing test_cstack_peek_empty\n");
    struct CStack *stack = cstack_create();

    void *peeked = cstack_peek(stack);
    if (peeked != NULL) {
        printf("FAILED: Peek on empty stack should return NULL\n");
        return;
    }

    cstack_free(stack);
    printf("PASSED test_cstack_peek_empty\n");
}

void test_cstack_lifo_order() {
    printf("Testing test_cstack_lifo_order\n");
    struct CStack *stack = cstack_create();

    int *a = malloc(sizeof(int));
    *a = 1;
    int *b = malloc(sizeof(int));
    *b = 2;
    int *c = malloc(sizeof(int));
    *c = 3;

    cstack_push(stack, a);
    cstack_push(stack, b);
    cstack_push(stack, c);

    int *popped = cstack_pop(stack);
    if (*popped != 3) {
        printf("FAILED: First pop should be 3\n");
        return;
    }
    free(popped);

    popped = cstack_pop(stack);
    if (*popped != 2) {
        printf("FAILED: Second pop should be 2\n");
        return;
    }
    free(popped);

    popped = cstack_pop(stack);
    if (*popped != 1) {
        printf("FAILED: Third pop should be 1\n");
        return;
    }
    free(popped);

    cstack_free(stack);
    printf("PASSED test_cstack_lifo_order\n");
}

void test_cstack_all() {
    test_cstack_create();
    test_cstack_push();
    test_cstack_pop();
    test_cstack_pop_empty();
    test_cstack_peek();
    test_cstack_peek_empty();
    test_cstack_lifo_order();
}

int main() {
    test_cstack_all();
    return 0;
}
