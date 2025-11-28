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

int main() {
    struct CBST *tree = cbst_create(int_compare);

    int *a = malloc(sizeof(int)); *a = 50;
    int *b = malloc(sizeof(int)); *b = 30;
    int *c = malloc(sizeof(int)); *c = 70;
    int *d = malloc(sizeof(int)); *d = 20;
    int *e = malloc(sizeof(int)); *e = 40;

    cbst_insert(tree, a);
    cbst_insert(tree, b);
    cbst_insert(tree, c);
    cbst_insert(tree, d);
    cbst_insert(tree, e);

    printf("Tree size: %zu\n", cbst_size(tree));
    printf("Min: %d\n", *(int *)cbst_min(tree));
    printf("Max: %d\n", *(int *)cbst_max(tree));

    int search_val = 30;
    int *found = cbst_search(tree, &search_val);
    printf("Search 30: %s\n", found ? "found" : "not found");

    search_val = 99;
    found = cbst_search(tree, &search_val);
    printf("Search 99: %s\n", found ? "found" : "not found");

    int delete_val = 30;
    cbst_delete(tree, &delete_val);
    printf("After deleting 30, size: %zu\n", cbst_size(tree));

    cbst_free(tree);

    return 0;
}
