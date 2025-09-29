#include "include/clinklist.h"
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <stdio.h>

int main() {
    
    struct CLinkedList *ll = clinklist_create();

    // initial size:
    printf("CLinklist data size: %zu\n", (malloc_usable_size(ll->data)));

    // add some items
    for (size_t i = 0; i < 10; i++) {
        int *value = malloc(sizeof(int));
        clinklist_push(ll, value);
    }

    // size after adding items:
    printf("CLinklist data size: %zu\n", (malloc_usable_size(ll->data)));

    // get an item
    int *item = (int *)clinklist_get(ll, 2);
    printf("Item at index 2: %d\n", *item);

    // contains an item
    if(clinklist_contains(ll, item) != 2) {
        printf("FAILED: CLinkedlist does not contain item\n");
        return 1;
    }

    // set an item
    int *new_value = malloc(sizeof(int));
    *new_value = 99;
    clinklist_set(ll, 2, new_value);
    printf("Item at index 2 after setting: %d\n", *(int *)clinklist_get(ll, 2));    

    // delete an item
    clinklist_delete_at_index(ll, 2);
    printf("Item at index 2 after deletion: %d\n", *(int *)clinklist_get(ll, 2));

    // size after deleting items:
    printf("CLinklist data size: %zu\n", (malloc_usable_size(ll->data)));


    // free the list
    printf("Freeing list\n");
    clinklist_free(ll);
    return 0;
}