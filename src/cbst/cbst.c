#include "cbst.h"

#include <stdlib.h>

struct CBST *cbst_create(compare_func_t compare) {
  struct CBST *tree = malloc(sizeof(struct CBST));
  tree->root = NULL;
  tree->size = 0;
  tree->compare = compare;
  return tree;
}

static void free_node(struct CBSTNode *node) {
  if (node == NULL) {
    return;
  }
  free_node(node->left);
  free_node(node->right);
  free(node->data);
  free(node);
}

void cbst_free(struct CBST *tree) {
  free_node(tree->root);
  free(tree);
}

static struct CBSTNode *insert_node(struct CBSTNode *node, void *data,
                                    compare_func_t compare, bool *inserted) {
  if (node == NULL) {
    struct CBSTNode *new_node = malloc(sizeof(struct CBSTNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    *inserted = true;
    return new_node;
  }

  int cmp = compare(data, node->data);
  if (cmp < 0) {
    node->left = insert_node(node->left, data, compare, inserted);
  } else if (cmp > 0) {
    node->right = insert_node(node->right, data, compare, inserted);
  } else {
    free(node->data);
    node->data = data;
  }
  return node;
}

void cbst_insert(struct CBST *tree, void *data) {
  bool inserted = false;
  tree->root = insert_node(tree->root, data, tree->compare, &inserted);
  if (inserted) {
    tree->size++;
  }
}

static struct CBSTNode *search_node(struct CBSTNode *node, const void *data,
                                    compare_func_t compare) {
  if (node == NULL) {
    return NULL;
  }

  int cmp = compare(data, node->data);
  if (cmp < 0) {
    return search_node(node->left, data, compare);
  } else if (cmp > 0) {
    return search_node(node->right, data, compare);
  }
  return node;
}

void *cbst_search(struct CBST *tree, const void *data) {
  struct CBSTNode *node = search_node(tree->root, data, tree->compare);
  if (node == NULL) {
    return NULL;
  }
  return node->data;
}

bool cbst_contains(struct CBST *tree, const void *data) {
  return cbst_search(tree, data) != NULL;
}

static struct CBSTNode *find_min_node(struct CBSTNode *node) {
  while (node->left != NULL) {
    node = node->left;
  }
  return node;
}

static struct CBSTNode *delete_min_node(struct CBSTNode *node) {
  if (node->left == NULL) {
    struct CBSTNode *right = node->right;
    free(node);
    return right;
  }
  node->left = delete_min_node(node->left);
  return node;
}

static struct CBSTNode *delete_node(struct CBSTNode *node, const void *data,
                                    compare_func_t compare, bool *deleted) {
  if (node == NULL) {
    return NULL;
  }

  int cmp = compare(data, node->data);
  if (cmp < 0) {
    node->left = delete_node(node->left, data, compare, deleted);
  } else if (cmp > 0) {
    node->right = delete_node(node->right, data, compare, deleted);
  } else {
    *deleted = true;
    if (node->left == NULL) {
      struct CBSTNode *right = node->right;
      free(node->data);
      free(node);
      return right;
    } else if (node->right == NULL) {
      struct CBSTNode *left = node->left;
      free(node->data);
      free(node);
      return left;
    } else {
      struct CBSTNode *min = find_min_node(node->right);
      free(node->data);
      node->data = min->data;
      min->data = NULL;
      node->right = delete_min_node(node->right);
    }
  }
  return node;
}

void cbst_delete(struct CBST *tree, const void *data) {
  bool deleted = false;
  tree->root = delete_node(tree->root, data, tree->compare, &deleted);
  if (deleted) {
    tree->size--;
  }
}

size_t cbst_size(struct CBST *tree) { return tree->size; }

void *cbst_min(struct CBST *tree) {
  if (tree->root == NULL) {
    return NULL;
  }
  return find_min_node(tree->root)->data;
}

static struct CBSTNode *find_max_node(struct CBSTNode *node) {
  while (node->right != NULL) {
    node = node->right;
  }
  return node;
}

void *cbst_max(struct CBST *tree) {
  if (tree->root == NULL) {
    return NULL;
  }
  return find_max_node(tree->root)->data;
}
