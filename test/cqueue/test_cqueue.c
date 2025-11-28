#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cqueue.h"

void test_cqueue_create() {
    printf("Testing test_cqueue_create\n");
    struct CQueue *queue = cqueue_create();

    if (queue == NULL) {
        printf("FAILED: Failed to create queue\n");
        return;
    }

    if (cqueue_size(queue) != 0) {
        printf("FAILED: Queue size is not 0\n");
        return;
    }

    if (!cqueue_is_empty(queue)) {
        printf("FAILED: Queue should be empty\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_create\n");
}

void test_cqueue_enqueue() {
    printf("Testing test_cqueue_enqueue\n");
    struct CQueue *queue = cqueue_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");

    cqueue_enqueue(queue, str1);
    cqueue_enqueue(queue, str2);

    if (cqueue_size(queue) != 2) {
        printf("FAILED: Queue size is not 2\n");
        return;
    }

    if (cqueue_is_empty(queue)) {
        printf("FAILED: Queue should not be empty\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_enqueue\n");
}

void test_cqueue_dequeue() {
    printf("Testing test_cqueue_dequeue\n");
    struct CQueue *queue = cqueue_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");

    cqueue_enqueue(queue, str1);
    cqueue_enqueue(queue, str2);

    char *dequeued = cqueue_dequeue(queue);
    if (strcmp(dequeued, "Hello") != 0) {
        printf("FAILED: Dequeued value is not Hello\n");
        return;
    }
    free(dequeued);

    if (cqueue_size(queue) != 1) {
        printf("FAILED: Queue size is not 1\n");
        return;
    }

    dequeued = cqueue_dequeue(queue);
    if (strcmp(dequeued, "World") != 0) {
        printf("FAILED: Dequeued value is not World\n");
        return;
    }
    free(dequeued);

    if (cqueue_size(queue) != 0) {
        printf("FAILED: Queue size is not 0\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_dequeue\n");
}

void test_cqueue_dequeue_empty() {
    printf("Testing test_cqueue_dequeue_empty\n");
    struct CQueue *queue = cqueue_create();

    void *dequeued = cqueue_dequeue(queue);
    if (dequeued != NULL) {
        printf("FAILED: Dequeue on empty queue should return NULL\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_dequeue_empty\n");
}

void test_cqueue_peek() {
    printf("Testing test_cqueue_peek\n");
    struct CQueue *queue = cqueue_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");

    cqueue_enqueue(queue, str1);
    cqueue_enqueue(queue, str2);

    char *peeked = cqueue_peek(queue);
    if (strcmp(peeked, "Hello") != 0) {
        printf("FAILED: Peeked value is not Hello\n");
        return;
    }

    if (cqueue_size(queue) != 2) {
        printf("FAILED: Queue size should still be 2 after peek\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_peek\n");
}

void test_cqueue_peek_empty() {
    printf("Testing test_cqueue_peek_empty\n");
    struct CQueue *queue = cqueue_create();

    void *peeked = cqueue_peek(queue);
    if (peeked != NULL) {
        printf("FAILED: Peek on empty queue should return NULL\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_peek_empty\n");
}

void test_cqueue_dequeue_single_element() {
    printf("Testing test_cqueue_dequeue_single_element\n");
    struct CQueue *queue = cqueue_create();

    char *str = malloc(6);
    strcpy(str, "Hello");

    cqueue_enqueue(queue, str);

    if (cqueue_size(queue) != 1) {
        printf("FAILED: Queue size is not 1\n");
        return;
    }

    char *dequeued = cqueue_dequeue(queue);
    if (strcmp(dequeued, "Hello") != 0) {
        printf("FAILED: Dequeued value is not Hello\n");
        return;
    }
    free(dequeued);

    if (cqueue_size(queue) != 0) {
        printf("FAILED: Queue size is not 0 after dequeue\n");
        return;
    }

    if (!cqueue_is_empty(queue)) {
        printf("FAILED: Queue should be empty after dequeue\n");
        return;
    }

    // Verify queue is still usable after becoming empty
    char *str2 = malloc(6);
    strcpy(str2, "World");
    cqueue_enqueue(queue, str2);

    if (cqueue_size(queue) != 1) {
        printf("FAILED: Queue size is not 1 after re-enqueue\n");
        return;
    }

    cqueue_free(queue);
    printf("PASSED test_cqueue_dequeue_single_element\n");
}

void test_cqueue_fifo_order() {
    printf("Testing test_cqueue_fifo_order\n");
    struct CQueue *queue = cqueue_create();

    int *a = malloc(sizeof(int));
    *a = 1;
    int *b = malloc(sizeof(int));
    *b = 2;
    int *c = malloc(sizeof(int));
    *c = 3;

    cqueue_enqueue(queue, a);
    cqueue_enqueue(queue, b);
    cqueue_enqueue(queue, c);

    int *dequeued = cqueue_dequeue(queue);
    if (*dequeued != 1) {
        printf("FAILED: First dequeue should be 1\n");
        return;
    }
    free(dequeued);

    dequeued = cqueue_dequeue(queue);
    if (*dequeued != 2) {
        printf("FAILED: Second dequeue should be 2\n");
        return;
    }
    free(dequeued);

    dequeued = cqueue_dequeue(queue);
    if (*dequeued != 3) {
        printf("FAILED: Third dequeue should be 3\n");
        return;
    }
    free(dequeued);

    cqueue_free(queue);
    printf("PASSED test_cqueue_fifo_order\n");
}

void test_cqueue_all() {
    test_cqueue_create();
    test_cqueue_enqueue();
    test_cqueue_dequeue();
    test_cqueue_dequeue_empty();
    test_cqueue_dequeue_single_element();
    test_cqueue_peek();
    test_cqueue_peek_empty();
    test_cqueue_fifo_order();
}

int main() {
    test_cqueue_all();
    return 0;
}
