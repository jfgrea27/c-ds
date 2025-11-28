#ifndef CBST_H
#define CBST_H

#include <stddef.h>
#include <stdbool.h>

typedef int (*compare_func_t)(const void *a, const void *b);

struct CBSTNode {
    void *data;
    struct CBSTNode *left;
    struct CBSTNode *right;
};

struct CBST {
    struct CBSTNode *root;
    size_t size;
    compare_func_t compare;
};

struct CBST *cbst_create(compare_func_t compare);

void cbst_free(struct CBST *tree);

void cbst_insert(struct CBST *tree, void *data);

void *cbst_search(struct CBST *tree, const void *data);

bool cbst_contains(struct CBST *tree, const void *data);

void cbst_delete(struct CBST *tree, const void *data);

size_t cbst_size(struct CBST *tree);

void *cbst_min(struct CBST *tree);

void *cbst_max(struct CBST *tree);

#endif
