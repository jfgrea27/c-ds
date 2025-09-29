#ifndef CLINKLIST_H
#define CLINKLIST_H

#include <stddef.h>

struct CLinkedList {
    void *data;
    struct CLinkedList *next;
};

struct CLinkedList *clinklist_create();

void clinklist_free(struct CLinkedList *clinklist);

void clinklist_push(struct CLinkedList *clinklist, void *data);

void* clinklist_get(struct CLinkedList *clinklist, size_t index);

int clinklist_contains(struct CLinkedList *clinklist, void *data);

void clinklist_set(struct CLinkedList *clinklist, size_t index, void *data);

void clinklist_delete_at_index(struct CLinkedList *clinklist, size_t index);

size_t clinklist_size(struct CLinkedList *clinklist);
 
#endif