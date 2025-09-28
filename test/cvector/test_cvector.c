#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/cvector/include/cvector.h"

void test_cvector_create() {
    printf("Testing test_cvector_create\n");
    struct CVector *vec = cvector_create();

    if (vec == NULL) {
        printf("FAILED: Failed to create vector\n");
        return;
    }

    if (vec->size != 0) {
        printf("FAILED: Vector size is not 0\n");
        return;
    }

    if (vec->capacity != INITIAL_CAPACITY) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY);
        return;
    }
    cvector_free(vec);

    printf("PASSED test_cvector_create\n");
}

void test_cvector_push_initial_capacity() {
    printf("Testing test_cvector_push_initial_capacity\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_push(vec, "World");
    cvector_push(vec, "!");

    if (vec->size != 3) {
        printf("FAILED: Vector size is not 3\n");
        return;
    }

    if (vec->capacity != INITIAL_CAPACITY) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY);
        return;
    }


    cvector_free(vec);
    printf("PASSED test_cvector_push_initial_capacity\n");
}

void test_cvector_push_double_capacity() {
    printf("Testing test_cvector_push_double_capacity\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_push(vec, "World");
    cvector_push(vec, "!");
    cvector_push(vec, "?");
    cvector_push(vec, ".");

    if (vec->size != 5) {
        printf("FAILED: Vector size is not 5\n");
        return;
    }
    
    if (vec->capacity != INITIAL_CAPACITY * 2) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY * 2);
        return;
    }

    cvector_free(vec);
    printf("PASSED test_cvector_push_double_capacity\n");
}


void test_cvector_get() {
    printf("Testing test_cvector_get\n");
    struct CVector *vec = cvector_create();

    cvector_push(vec, "Hello");


    if (strcmp(cvector_get(vec, 0), "Hello") != 0) {
        printf("FAILED: Vector data is not Hello\n");
        return;
    }

    if (cvector_get(vec, 100) != NULL) {
        printf("FAILED: Vector data is not NULL\n");
        return;
    }

    cvector_free(vec);
    printf("PASSED test_cvector_get\n");
}

void test_cvector_set() {
    printf("Testing test_cvector_set\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_set(vec, 0, "World");

    if (strcmp(cvector_get(vec, 0), "World") != 0) {
        printf("FAILED: Vector data is not World\n");
        return;
    }
    
    if(vec->size != 1) {
        printf("FAILED: Vector size is not 1\n");
        return;
    }
    if(vec->capacity != INITIAL_CAPACITY) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY);
        return;
    }

    cvector_free(vec);
    printf("PASSED test_cvector_set\n");
}

void test_cvector_delete_last_item() {
    printf("Testing test_cvector_delete_last_item\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_push(vec, "World");
    cvector_push(vec, "!");

    cvector_delete(vec, 2);

    if (strcmp(cvector_get(vec, 0), "Hello") != 0) {
        printf("FAILED: Vector data is not Hello\n");
        return;
    }
    
    if (strcmp(cvector_get(vec, 1), "World") != 0) {
        printf("FAILED: Vector data is not World\n");
        return;
    }
    
    
    if(vec->size != 2) {
        printf("FAILED: Vector size is not 2\n");
        return;
    }
    if(vec->capacity != INITIAL_CAPACITY) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY);
        return;
    }

    cvector_free(vec);
    printf("PASSED test_cvector_delete_last_item\n");
}

void test_cvector_delete_middle_item() {
    printf("Testing test_cvector_delete_middle_item\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_push(vec, "World");
    cvector_push(vec, "!");

    cvector_delete(vec, 1);

    if (strcmp(cvector_get(vec, 0), "Hello") != 0) {
        printf("FAILED: Vector data is not Hello\n");
        return;
    }
    
    

    if (strcmp(cvector_get(vec, 1), "!") != 0) {
        printf("FAILED: Vector data is not !\n");
        return;
    }
    
    if(vec->size != 2) {
        printf("FAILED: Vector size is not 2\n");
        return;
    }
    if(vec->capacity != INITIAL_CAPACITY) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY);
        return;
    }

    cvector_free(vec);
    printf("PASSED test_cvector_delete_middle_item\n");
}


void test_cvector_delete_out_of_bounds() {
    printf("Testing test_cvector_delete_out_of_bounds\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_push(vec, "World");
    cvector_push(vec, "!");

    cvector_delete(vec, 3);

    if(vec->size != 3) {
        printf("FAILED: Vector size is not 3\n");
        return;
    }
    if(vec->capacity != INITIAL_CAPACITY) {
        printf("FAILED: Vector capacity is not %d\n", INITIAL_CAPACITY);
        return;
    }

    cvector_free(vec);
    printf("PASSED test_cvector_delete_out_of_bounds\n");
}

void test_cvector_size() {
    printf("Testing test_cvector_size\n");
    struct CVector *vec = cvector_create();
    cvector_push(vec, "Hello");
    cvector_push(vec, "World");
    cvector_push(vec, "!");
    
    if(cvector_size(vec) != 3) {
        printf("FAILED: Vector size is not 3\n");
        return;
    }
    
    cvector_free(vec);
    printf("PASSED test_cvector_size\n");
}

void test_cvector_all() {
    test_cvector_create();
    test_cvector_push_initial_capacity();
    test_cvector_push_double_capacity();
    test_cvector_get();
    test_cvector_set();
    test_cvector_delete_last_item();
    test_cvector_delete_middle_item();
    test_cvector_delete_out_of_bounds();
    test_cvector_size();
}


int main() {
    test_cvector_all();
    return 0;
}