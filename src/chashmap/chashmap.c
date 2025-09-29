#include "include/chashmap.h"
// #include "include/clinklist.h"

#include <stdint.h>


int mem_hasher(void* p) {
    if (p == NULL) {
        return -1;
    }

    int addr = *(int *)p;
    return addr % NUMBER_BUCKETS;

}

struct CHashMap *chashmap_create() {
    struct CHashMap *chashmap = malloc(sizeof(struct CHashMap));
    chashmap->size = 0;
    chashmap->hash = mem_hasher;
    chashmap->buckets = NULL;
    return chashmap;
}
