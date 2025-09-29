#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <stdio.h>

#include "include/cvector.h"


/*
* end-to-end test of cvector
*/
        
int main(int argc, char *argv[]) {

    struct CVector *vec = cvector_create();

    // initial size:
    printf("CVector data size: %zu\n", (malloc_usable_size(vec->data)));

    // add some items
    for (size_t i = 0; i < 10; i++) {
        int *value = malloc(sizeof(int));
        cvector_push(vec, value);
    }
  
    // size after adding items:
    printf("CVector data size: %zu\n", (malloc_usable_size(vec->data)));

    // get an item
    int *item = (int *)cvector_get(vec, 2);
    printf("Item at index 2: %d\n", *item);

    // set an item
    int* new_value = malloc(sizeof(int));
    *new_value = 99;
    printf("Setting item at index 2 to: %d\n", *new_value);
    cvector_set(vec, 2, new_value);
    printf("New item at index 2: %d\n", *(int *)cvector_get(vec, 2));

    // delete an item
    printf("Deleting item at index 1\n");
    cvector_delete(vec, 1);
    printf("Item at index 1 after deletion: %d\n", *(int *)cvector_get(vec, 1));

    // free the vector
    printf("Freeing vector\n");
    cvector_free(vec);


    return 0;
}