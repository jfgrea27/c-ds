#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../src/clinklist/include/clinklist.h"

void test_clinklist_create() {
    printf("Testing test_clinklist_create\n");
    struct CLinkedList *ll = clinklist_create();

    if (ll == NULL) {
        printf("FAILED: Failed to create vector\n");
        return;
    }

    if (ll->data != NULL) {
        printf("FAILED: CLinkedlist data is not NULL\n");
        return;
    }

    if (ll->next != NULL) {
        printf("FAILED: CLinkedlist next is not NULL\n");
        return;
    }
    clinklist_free(ll);

    printf("PASSED test_clinklist_create\n");
}

void test_clinklist_push() {
    printf("Testing test_clinklist_push\n");
    struct CLinkedList *ll = clinklist_create();

    // add some from heap
    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");
    char *str3 = malloc(2);
    strcpy(str3, "!");
    clinklist_push(ll, str1);
    clinklist_push(ll, str2);
    clinklist_push(ll, str3);

    // iterate through the list and check if the data is correct
    if (strcmp(ll->data, "Hello") != 0) {
        printf("FAILED: CLinkedlist 0th data is not Hello\n");
        return;
    }
    if (strcmp(ll->next->data, "World") != 0) {
        printf("FAILED: CLinkedlist 1st data is not World\n");
        return;
    }
    if (strcmp(ll->next->next->data, "!") != 0) {
        printf("FAILED: CLinkedlist 2nd data is not !\n");
        return;
    }
    if (ll->next->next->next != NULL) {
        printf("FAILED: CLinkedlist 3rd next is not NULL\n");
        return;
    }

    clinklist_free(ll);
    printf("PASSED test_clinklist_push\n");
}

void test_clinklist_get() {
    printf("Testing test_clinklist_get\n");
    struct CLinkedList *ll = clinklist_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");
    clinklist_push(ll, str1);
    clinklist_push(ll, str2);


    if (strcmp(clinklist_get(ll, 0), "Hello") != 0) {
        printf("FAILED: Vector data is not Hello\n");
        return;
    }

    if (strcmp(clinklist_get(ll, 1), "World") != 0) {
        printf("FAILED: Vector data is not World\n");
        return;
    }

    if (clinklist_get(ll, 100) != NULL) {
        printf("FAILED: Vector data is not NULL\n");
        return;
    }

    clinklist_free(ll);
    printf("PASSED test_clinklist_get\n");
}

void test_clinklist_contains() {
    printf("Testing test_clinklist_contains\n");
    struct CLinkedList *ll = clinklist_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    clinklist_push(ll, str1);
    char *str2 = malloc(6);
    strcpy(str2, "World");
    clinklist_push(ll, str2);
    char *str3 = malloc(2);
    strcpy(str3, "!");

    if(clinklist_contains(ll, str1) != 0) {
        printf("FAILED: CLinkedlist does not contain Hello\n");
        return;
    }
    if(clinklist_contains(ll, str3) != -1) {
        printf("FAILED: CLinkedlist contains !\n");
        return;
    }

    clinklist_free(ll);
    printf("PASSED test_clinklist_contains\n");
}

void test_clinklist_contains_empty() {
    printf("Testing test_clinklist_contains_empty\n");
    struct CLinkedList *ll = clinklist_create();

    if(clinklist_contains(ll, "Hello") != -1) {
        printf("FAILED: CLinkedlist contains Hello\n");
        return;
    }

    clinklist_free(ll);
    printf("PASSED test_clinklist_contains_empty\n");
}

void test_clinklist_set() {
    printf("Testing test_clinklist_set\n");
    struct CLinkedList *ll = clinklist_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");
    clinklist_push(ll, str1);
    clinklist_push(ll, str2);

    // set the first item to World
    char *str3 = malloc(10);
    strcpy(str3, "New world");
    clinklist_set(ll, 0, str3);
    
    if(clinklist_size(ll) != 2) {
        printf("FAILED: CLinkedlist size is not 2\n");
        return;
    }
    // get the first item
    if(strcmp(clinklist_get(ll, 0), "New world") != 0) {
        printf("FAILED: CLinkedlist data is not New world\n");
        return;
    }

    // set the second item 
    char* str4 = malloc(12);
    strcpy(str4, "New world 2");
    clinklist_set(ll, 1, str4);
    // get the second item
    if(strcmp(clinklist_get(ll, 1), "New world 2") != 0) {
        printf("FAILED: CLinkedlist data is not New world 2\n");
        return;
    }

    // set out of bounds
    char *str5 = malloc(12);
    strcpy(str5, "New world 3");
    clinklist_set(ll, 100, str5);
    // get the second item
    if(strcmp(clinklist_get(ll, 1), "New world 2") != 0) {
        printf("FAILED: CLinkedlist data is not New world 2 (should not change)\n");
        return;
    }

    clinklist_free(ll);
    printf("PASSED test_clinklist_set\n");
}

void test_clinklist_delete_at_index() {
    printf("Testing test_clinklist_delete_at_index\n");
    struct CLinkedList *ll = clinklist_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");
    char *str3 = malloc(2);
    strcpy(str3, "!");
    clinklist_push(ll, str1);
    clinklist_push(ll, str2);
    clinklist_push(ll, str3);

    clinklist_delete_at_index(ll, 2);

    if(strcmp(clinklist_get(ll, 0), "Hello") != 0) {
        printf("FAILED: CLinkedlist data is not Hello\n");
        return;
    }
    if(strcmp(clinklist_get(ll, 1), "World") != 0) {
        printf("FAILED: CLinkedlist data is not World\n");
        return;
    }

    if(clinklist_size(ll) != 2) {
        printf("FAILED: CLinkedlist size is not 2\n");
        return;
    }

    clinklist_free(ll);
    printf("PASSED test_clinklist_delete_at_index\n");
}

void test_clinklist_size() {
    printf("Testing test_clinklist_size\n");
    struct CLinkedList *ll = clinklist_create();

    char *str1 = malloc(6);
    strcpy(str1, "Hello");
    char *str2 = malloc(6);
    strcpy(str2, "World");
    char *str3 = malloc(2);
    strcpy(str3, "!");
    clinklist_push(ll, str1);
    clinklist_push(ll, str2);
    clinklist_push(ll, str3);

    if(clinklist_size(ll) != 3) {
        printf("FAILED: Vector size is not 3\n");
        return;
    }
    
    clinklist_free(ll);
    printf("PASSED test_clinklist_size\n");
}

void test_clinklist_all() {

    test_clinklist_create();
    test_clinklist_push();
    test_clinklist_get();
    test_clinklist_contains();
    test_clinklist_contains_empty();
    test_clinklist_set();
    test_clinklist_delete_at_index();
    test_clinklist_size();
}


int main() {
    test_clinklist_all();
    return 0;
}