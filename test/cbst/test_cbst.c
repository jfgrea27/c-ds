#include <stdio.h>
#include <stdlib.h>

#include "cbst.h"

int int_compare(const void *a, const void *b) {
    int val_a = *(int *)a;
    int val_b = *(int *)b;
    if (val_a < val_b) return -1;
    if (val_a > val_b) return 1;
    return 0;
}

void test_cbst_create() {
    printf("Testing test_cbst_create\n");
    struct CBST *tree = cbst_create(int_compare);

    if (tree == NULL) {
        printf("FAILED: Failed to create tree\n");
        return;
    }

    if (cbst_size(tree) != 0) {
        printf("FAILED: Tree size is not 0\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_create\n");
}

void test_cbst_insert() {
    printf("Testing test_cbst_insert\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 5;
    int *c = malloc(sizeof(int)); *c = 15;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);

    if (cbst_size(tree) != 3) {
        printf("FAILED: Tree size is not 3\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_insert\n");
}

void test_cbst_search() {
    printf("Testing test_cbst_search\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 5;
    int *c = malloc(sizeof(int)); *c = 15;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);

    int search_val = 5;
    int *found = cbst_search(tree, &search_val);
    if (found == NULL || *found != 5) {
        printf("FAILED: Could not find 5\n");
        return;
    }

    search_val = 99;
    found = cbst_search(tree, &search_val);
    if (found != NULL) {
        printf("FAILED: Should not find 99\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_search\n");
}

void test_cbst_contains() {
    printf("Testing test_cbst_contains\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    cbst_insert(tree, a);

    int search_val = 10;
    if (!cbst_contains(tree, &search_val)) {
        printf("FAILED: Should contain 10\n");
        return;
    }

    search_val = 99;
    if (cbst_contains(tree, &search_val)) {
        printf("FAILED: Should not contain 99\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_contains\n");
}

void test_cbst_min_max() {
    printf("Testing test_cbst_min_max\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 50;
    int *b = malloc(sizeof(int)); *b = 25;
    int *c = malloc(sizeof(int)); *c = 75;
    int *d = malloc(sizeof(int)); *d = 10;
    int *e = malloc(sizeof(int)); *e = 100;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);
    cbst_insert(tree, d);
    cbst_insert(tree, e);

    int *min = cbst_min(tree);
    if (min == NULL || *min != 10) {
        printf("FAILED: Min should be 10\n");
        return;
    }

    int *max = cbst_max(tree);
    if (max == NULL || *max != 100) {
        printf("FAILED: Max should be 100\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_min_max\n");
}

void test_cbst_min_max_empty() {
    printf("Testing test_cbst_min_max_empty\n");
    struct CBST *tree = cbst_create(int_compare);

    if (cbst_min(tree) != NULL) {
        printf("FAILED: Min of empty tree should be NULL\n");
        return;
    }

    if (cbst_max(tree) != NULL) {
        printf("FAILED: Max of empty tree should be NULL\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_min_max_empty\n");
}

void test_cbst_delete_leaf() {
    printf("Testing test_cbst_delete_leaf\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 5;
    int *c = malloc(sizeof(int)); *c = 15;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);

    int delete_val = 5;
    cbst_delete(tree, &delete_val);

    if (cbst_size(tree) != 2) {
        printf("FAILED: Tree size should be 2\n");
        return;
    }

    if (cbst_contains(tree, &delete_val)) {
        printf("FAILED: Should not contain 5\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_delete_leaf\n");
}

void test_cbst_delete_one_child() {
    printf("Testing test_cbst_delete_one_child\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 5;
    int *c = malloc(sizeof(int)); *c = 3;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);

    int delete_val = 5;
    cbst_delete(tree, &delete_val);

    if (cbst_size(tree) != 2) {
        printf("FAILED: Tree size should be 2\n");
        return;
    }

    int search_val = 3;
    if (!cbst_contains(tree, &search_val)) {
        printf("FAILED: Should still contain 3\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_delete_one_child\n");
}

void test_cbst_delete_two_children() {
    printf("Testing test_cbst_delete_two_children\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 5;
    int *c = malloc(sizeof(int)); *c = 15;
    int *d = malloc(sizeof(int)); *d = 3;
    int *e = malloc(sizeof(int)); *e = 7;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);
    cbst_insert(tree, d);
    cbst_insert(tree, e);

    int delete_val = 5;
    cbst_delete(tree, &delete_val);

    if (cbst_size(tree) != 4) {
        printf("FAILED: Tree size should be 4\n");
        return;
    }

    int search_val = 3;
    if (!cbst_contains(tree, &search_val)) {
        printf("FAILED: Should still contain 3\n");
        return;
    }

    search_val = 7;
    if (!cbst_contains(tree, &search_val)) {
        printf("FAILED: Should still contain 7\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_delete_two_children\n");
}

void test_cbst_delete_nonexistent() {
    printf("Testing test_cbst_delete_nonexistent\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    cbst_insert(tree, a);

    int delete_val = 99;
    cbst_delete(tree, &delete_val);

    if (cbst_size(tree) != 1) {
        printf("FAILED: Tree size should still be 1\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_delete_nonexistent\n");
}

void test_cbst_insert_duplicate() {
    printf("Testing test_cbst_insert_duplicate\n");
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 10;
    int *b = malloc(sizeof(int)); *b = 10;

    cbst_insert(tree, a);
    cbst_insert(tree, b);

    if (cbst_size(tree) != 1) {
        printf("FAILED: Tree size should be 1 (duplicate replaced)\n");
        return;
    }

    cbst_free(tree);
    printf("PASSED test_cbst_insert_duplicate\n");
}

void test_cbst_all() {
    test_cbst_create();
    test_cbst_insert();
    test_cbst_search();
    test_cbst_contains();
    test_cbst_min_max();
    test_cbst_min_max_empty();
    test_cbst_delete_leaf();
    test_cbst_delete_one_child();
    test_cbst_delete_two_children();
    test_cbst_delete_nonexistent();
    test_cbst_insert_duplicate();
}

int main() {
    test_cbst_all();
    return 0;
}
