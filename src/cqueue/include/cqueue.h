#ifndef CQUEUE_H
#define CQUEUE_H

#include <stddef.h>
#include <stdbool.h>

struct CLinkedList;

struct CQueue {
    struct CLinkedList *data;
};

struct CQueue *cqueue_create();

void cqueue_free(struct CQueue *queue);

void cqueue_enqueue(struct CQueue *queue, void *item);

void *cqueue_dequeue(struct CQueue *queue);

void *cqueue_peek(struct CQueue *queue);

bool cqueue_is_empty(struct CQueue *queue);

size_t cqueue_size(struct CQueue *queue);

#endif
