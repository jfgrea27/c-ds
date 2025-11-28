#include <stdio.h>
#include <stdlib.h>
#include "cqueue.h"

int main() {
    struct CQueue *queue = cqueue_create();

    int *a = malloc(sizeof(int));
    *a = 10;
    int *b = malloc(sizeof(int));
    *b = 20;
    int *c = malloc(sizeof(int));
    *c = 30;

    cqueue_enqueue(queue, a);
    cqueue_enqueue(queue, b);
    cqueue_enqueue(queue, c);

    printf("Queue size: %zu\n", cqueue_size(queue));

    int *front = cqueue_dequeue(queue);
    printf("Dequeued: %d\n", *front);
    free(front);

    front = cqueue_peek(queue);
    printf("Peek: %d\n", *front);

    printf("Queue size: %zu\n", cqueue_size(queue));
    printf("Is empty: %s\n", cqueue_is_empty(queue) ? "true" : "false");

    cqueue_free(queue);

    return 0;
}
