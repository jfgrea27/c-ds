#ifndef CHASHMAP_H
#define CHASHMAP_H

#include <stddef.h>
#include <stdbool.h>

#define NUMBER_BUCKETS 16

typedef size_t (*hash_func_t)(const void *key);
typedef bool (*key_equals_t)(const void *a, const void *b);

struct CLinkedList;

struct HashEntry {
    void *key;
    void *value;
};

struct CHashMap {
    size_t size;
    hash_func_t hash;
    key_equals_t equals;
    struct CLinkedList **buckets;
};

struct CHashMap *chashmap_create(hash_func_t hash, key_equals_t equals);

void chashmap_free(struct CHashMap *chashmap);

void chashmap_put(struct CHashMap *chashmap, void *key, void *value);

void *chashmap_get(struct CHashMap *chashmap, const void *key);

bool chashmap_contains(struct CHashMap *chashmap, const void *key);

void chashmap_delete(struct CHashMap *chashmap, const void *key);

size_t chashmap_size(struct CHashMap *chashmap);

#endif
