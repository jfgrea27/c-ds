#include "chashmap.h"
#include "clinklist.h"

#include <stdlib.h>

struct CHashMap *chashmap_create(hash_func_t hash, key_equals_t equals) {
    struct CHashMap *chashmap = malloc(sizeof(struct CHashMap));
    chashmap->size = 0;
    chashmap->hash = hash;
    chashmap->equals = equals;
    chashmap->buckets = calloc(NUMBER_BUCKETS, sizeof(struct CLinkedList *));
    return chashmap;
}

void chashmap_free(struct CHashMap *chashmap) {
    for (size_t i = 0; i < NUMBER_BUCKETS; i++) {
        if (chashmap->buckets[i] != NULL) {
            struct CLinkedList *bucket = chashmap->buckets[i];
            size_t bucket_size = clinklist_size(bucket);
            for (size_t j = 0; j < bucket_size; j++) {
                struct HashEntry *entry = clinklist_get(bucket, j);
                if (entry != NULL) {
                    free(entry->key);
                    free(entry->value);
                }
            }
            clinklist_free(bucket);
        }
    }
    free(chashmap->buckets);
    free(chashmap);
}

static struct HashEntry *find_entry(struct CHashMap *chashmap, struct CLinkedList *bucket, const void *key) {
    size_t bucket_size = clinklist_size(bucket);
    for (size_t i = 0; i < bucket_size; i++) {
        struct HashEntry *entry = clinklist_get(bucket, i);
        if (entry != NULL && chashmap->equals(entry->key, key)) {
            return entry;
        }
    }
    return NULL;
}

void chashmap_put(struct CHashMap *chashmap, void *key, void *value) {
    size_t index = chashmap->hash(key) % NUMBER_BUCKETS;

    if (chashmap->buckets[index] == NULL) {
        chashmap->buckets[index] = clinklist_create();
    }

    struct CLinkedList *bucket = chashmap->buckets[index];
    struct HashEntry *existing = find_entry(chashmap, bucket, key);

    if (existing != NULL) {
        free(existing->value);
        existing->value = value;
        free(key);
    } else {
        struct HashEntry *entry = malloc(sizeof(struct HashEntry));
        entry->key = key;
        entry->value = value;
        clinklist_push(bucket, entry);
        chashmap->size++;
    }
}

void *chashmap_get(struct CHashMap *chashmap, const void *key) {
    size_t index = chashmap->hash(key) % NUMBER_BUCKETS;

    if (chashmap->buckets[index] == NULL) {
        return NULL;
    }

    struct HashEntry *entry = find_entry(chashmap, chashmap->buckets[index], key);
    if (entry != NULL) {
        return entry->value;
    }
    return NULL;
}

bool chashmap_contains(struct CHashMap *chashmap, const void *key) {
    return chashmap_get(chashmap, key) != NULL;
}

void chashmap_delete(struct CHashMap *chashmap, const void *key) {
    size_t index = chashmap->hash(key) % NUMBER_BUCKETS;

    if (chashmap->buckets[index] == NULL) {
        return;
    }

    struct CLinkedList *bucket = chashmap->buckets[index];
    size_t bucket_size = clinklist_size(bucket);

    for (size_t i = 0; i < bucket_size; i++) {
        struct HashEntry *entry = clinklist_get(bucket, i);
        if (entry != NULL && chashmap->equals(entry->key, key)) {
            free(entry->key);
            free(entry->value);
            clinklist_delete_at_index(bucket, i);
            chashmap->size--;
            return;
        }
    }
}

size_t chashmap_size(struct CHashMap *chashmap) {
    return chashmap->size;
}
