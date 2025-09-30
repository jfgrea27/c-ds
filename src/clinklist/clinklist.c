#include "clinklist.h"
#include <stdlib.h>
#include <stdio.h>

struct CLinkedList *clinklist_create() {
    struct CLinkedList *clinklist = malloc(sizeof(struct CLinkedList));
    clinklist->data = NULL;
    clinklist->next = NULL;
    return clinklist;
}

void clinklist_free(struct CLinkedList *clinklist) {
    if (clinklist == NULL) {
        return;
    }
    if (clinklist->data != NULL) {
        free(clinklist->data);
    }
    clinklist_free(clinklist->next);
    free(clinklist);
}

void clinklist_push(struct CLinkedList *clinklist, void *data) {

    // get the last node
    struct CLinkedList *current = clinklist;
    while (current->next != NULL) {
        current = current->next;
    }
    if (current->data == NULL) {
        current->data = data;
        return;
    }
    else {
        struct CLinkedList *new_node = malloc(sizeof(struct CLinkedList));
        new_node->data = data;
        new_node->next = NULL;
        current->next = new_node;
    }
}

void* clinklist_get(struct CLinkedList *clinklist, size_t index) {

    if (index >= clinklist_size(clinklist)) {
        return NULL;
    }
    struct CLinkedList *current = clinklist;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int clinklist_contains(struct CLinkedList *clinklist, void *data) {
    struct CLinkedList *current = clinklist;
    int index = 0;
    while (current != NULL) {
        if (current->data == data) {
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}

void clinklist_set(struct CLinkedList *clinklist, size_t index, void *data) {
    if (index >= clinklist_size(clinklist)) {
        return;
    }
    struct CLinkedList *current = clinklist;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    if (current->data != NULL) {
        free(current->data);
    }
    current->data = data;
}

void clinklist_delete_at_index(struct CLinkedList *clinklist, size_t index) {
    if (index >= clinklist_size(clinklist)) {
        return;
    }
    struct CLinkedList *current = clinklist;
    struct CLinkedList *previous = NULL;
    for (size_t i = 0; i < index; i++) {
        previous = current;
        current = current->next;
    }


    previous->next = current->next;
    // free the current
    if (current->data != NULL) {
        free(current->data);
        current->data = NULL;

    }
    free(current);
}

size_t clinklist_size(struct CLinkedList *clinklist) {
    if (clinklist == NULL) {
        return 0;
    }
    size_t size = 0;
    struct CLinkedList *current = clinklist;
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return size;
}

