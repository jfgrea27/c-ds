#include "cqueue.h"
#include "clinklist.h"

#include <stdlib.h>

struct CQueue *cqueue_create() {
    struct CQueue *queue = malloc(sizeof(struct CQueue));
    queue->data = clinklist_create();
    return queue;
}

void cqueue_free(struct CQueue *queue) {
    clinklist_free(queue->data);
    free(queue);
}

void cqueue_enqueue(struct CQueue *queue, void *item) {
    clinklist_push(queue->data, item);
}

void *cqueue_dequeue(struct CQueue *queue) {
    if (queue->data->data == NULL) {
        return NULL;
    }
    void *item = queue->data->data;
    queue->data->data = NULL;
    clinklist_delete_at_index(queue->data, 0);
    return item;
}

void *cqueue_peek(struct CQueue *queue) {
    return clinklist_get(queue->data, 0);
}

bool cqueue_is_empty(struct CQueue *queue) {
    return queue->data->data == NULL;
}

size_t cqueue_size(struct CQueue *queue) {
    if (queue->data->data == NULL) {
        return 0;
    }
    return clinklist_size(queue->data);
}
