#ifndef CHASHMAP_H
#define CHASHMAP_H

#include <stddef.h>

#define NUMBER_BUCKETS 10

typedef size_t (*hash_func_t)(const void *key);

struct CLinkedList; 

struct CHashMap {
    size_t size;
    hash_func_t hash;
    struct CLinkedList** buckets;
};

struct CHashMap* chashmap_create();

void chashmap_free(struct CHashMap *chashmap);

void chashmap_put(struct CHashMap *chashmap, const void *key, void *value);

void chashmap_get(struct CHashMap *chashmap, const void *key);

void chashmap_delete(struct CHashMap *chashmap, const void *key);

size_t clinklist_size(struct CLinkedList *clinklist);
 
#endif