#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chashmap.h"

size_t int_hash(const void *key) {
    return (size_t)(*(int *)key);
}

bool int_equals(const void *a, const void *b) {
    return *(int *)a == *(int *)b;
}

int main() {
    struct CHashMap *map = chashmap_create(int_hash, int_equals);

    int *key1 = malloc(sizeof(int));
    *key1 = 42;
    char *value1 = malloc(14);
    strcpy(value1, "Hello, World!");

    int *key2 = malloc(sizeof(int));
    *key2 = 100;
    char *value2 = malloc(8);
    strcpy(value2, "Goodbye");

    chashmap_put(map, key1, value1);
    chashmap_put(map, key2, value2);

    printf("Size: %zu\n", chashmap_size(map));

    int lookup = 42;
    char *retrieved = chashmap_get(map, &lookup);
    printf("Key 42: %s\n", retrieved);

    lookup = 100;
    retrieved = chashmap_get(map, &lookup);
    printf("Key 100: %s\n", retrieved);

    lookup = 999;
    retrieved = chashmap_get(map, &lookup);
    printf("Key 999: %s\n", retrieved ? retrieved : "(null)");

    chashmap_free(map);

    return 0;
}
