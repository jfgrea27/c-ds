#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chashmap.h"
#include "clinklist.h"

size_t int_hash(const void *key) { return (size_t)(*(int *)key); }

bool int_equals(const void *a, const void *b) { return *(int *)a == *(int *)b; }

void test_chashmap_create() {
  printf("Testing test_chashmap_create\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  if (map == NULL) {
    printf("FAILED: Failed to create hashmap\n");
    return;
  }

  if (chashmap_size(map) != 0) {
    printf("FAILED: Hashmap size is not 0\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_create\n");
}

void test_chashmap_put_and_get() {
  printf("Testing test_chashmap_put_and_get\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key = malloc(sizeof(int));
  *key = 42;
  char *value = malloc(6);
  strcpy(value, "Hello");

  chashmap_put(map, key, value);

  if (chashmap_size(map) != 1) {
    printf("FAILED: Hashmap size is not 1\n");
    return;
  }

  int lookup = 42;
  char *retrieved = chashmap_get(map, &lookup);
  if (retrieved == NULL || strcmp(retrieved, "Hello") != 0) {
    printf("FAILED: Retrieved value is not Hello\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_put_and_get\n");
}

void test_chashmap_get_nonexistent() {
  printf("Testing test_chashmap_get_nonexistent\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int lookup = 999;
  void *retrieved = chashmap_get(map, &lookup);
  if (retrieved != NULL) {
    printf("FAILED: Get on nonexistent key should return NULL\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_get_nonexistent\n");
}

void test_chashmap_put_multiple() {
  printf("Testing test_chashmap_put_multiple\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key1 = malloc(sizeof(int));
  *key1 = 1;
  char *value1 = malloc(4);
  strcpy(value1, "one");

  int *key2 = malloc(sizeof(int));
  *key2 = 2;
  char *value2 = malloc(4);
  strcpy(value2, "two");

  int *key3 = malloc(sizeof(int));
  *key3 = 3;
  char *value3 = malloc(6);
  strcpy(value3, "three");

  chashmap_put(map, key1, value1);
  chashmap_put(map, key2, value2);
  chashmap_put(map, key3, value3);

  if (chashmap_size(map) != 3) {
    printf("FAILED: Hashmap size is not 3\n");
    return;
  }

  int lookup = 1;
  if (strcmp(chashmap_get(map, &lookup), "one") != 0) {
    printf("FAILED: Key 1 value incorrect\n");
    return;
  }

  lookup = 2;
  if (strcmp(chashmap_get(map, &lookup), "two") != 0) {
    printf("FAILED: Key 2 value incorrect\n");
    return;
  }

  lookup = 3;
  if (strcmp(chashmap_get(map, &lookup), "three") != 0) {
    printf("FAILED: Key 3 value incorrect\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_put_multiple\n");
}

void test_chashmap_put_update() {
  printf("Testing test_chashmap_put_update\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key1 = malloc(sizeof(int));
  *key1 = 42;
  char *value1 = malloc(6);
  strcpy(value1, "Hello");

  chashmap_put(map, key1, value1);

  int *key2 = malloc(sizeof(int));
  *key2 = 42;
  char *value2 = malloc(6);
  strcpy(value2, "World");

  chashmap_put(map, key2, value2);

  if (chashmap_size(map) != 1) {
    printf("FAILED: Hashmap size should still be 1 after update\n");
    return;
  }

  int lookup = 42;
  char *retrieved = chashmap_get(map, &lookup);
  if (strcmp(retrieved, "World") != 0) {
    printf("FAILED: Value should be updated to World\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_put_update\n");
}

void test_chashmap_contains() {
  printf("Testing test_chashmap_contains\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key = malloc(sizeof(int));
  *key = 42;
  char *value = malloc(6);
  strcpy(value, "Hello");

  chashmap_put(map, key, value);

  int lookup = 42;
  if (!chashmap_contains(map, &lookup)) {
    printf("FAILED: Map should contain key 42\n");
    return;
  }

  lookup = 999;
  if (chashmap_contains(map, &lookup)) {
    printf("FAILED: Map should not contain key 999\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_contains\n");
}

void test_chashmap_delete() {
  printf("Testing test_chashmap_delete\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key1 = malloc(sizeof(int));
  *key1 = 1;
  char *value1 = malloc(4);
  strcpy(value1, "one");

  int *key2 = malloc(sizeof(int));
  *key2 = 2;
  char *value2 = malloc(4);
  strcpy(value2, "two");

  chashmap_put(map, key1, value1);
  chashmap_put(map, key2, value2);

  int lookup = 1;
  chashmap_delete(map, &lookup);

  if (chashmap_size(map) != 1) {
    printf("FAILED: Hashmap size should be 1 after delete\n");
    return;
  }

  if (chashmap_contains(map, &lookup)) {
    printf("FAILED: Key 1 should be deleted\n");
    return;
  }

  lookup = 2;
  if (!chashmap_contains(map, &lookup)) {
    printf("FAILED: Key 2 should still exist\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_delete\n");
}

void test_chashmap_delete_nonexistent() {
  printf("Testing test_chashmap_delete_nonexistent\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key = malloc(sizeof(int));
  *key = 42;
  char *value = malloc(6);
  strcpy(value, "Hello");

  chashmap_put(map, key, value);

  int lookup = 999;
  chashmap_delete(map, &lookup);

  if (chashmap_size(map) != 1) {
    printf("FAILED: Hashmap size should still be 1\n");
    return;
  }

  chashmap_free(map);
  printf("PASSED test_chashmap_delete_nonexistent\n");
}

void test_chashmap_collision() {
  printf("Testing test_chashmap_collision\n");
  struct CHashMap *map = chashmap_create(int_hash, int_equals);

  int *key1 = malloc(sizeof(int));
  *key1 = 1;
  char *value1 = malloc(4);
  strcpy(value1, "one");

  int *key2 = malloc(sizeof(int));
  *key2 = 1 + NUMBER_BUCKETS;
  char *value2 = malloc(4);
  strcpy(value2, "two");

  chashmap_put(map, key1, value1);
  chashmap_put(map, key2, value2);

  if (chashmap_size(map) != 2) {
    printf("FAILED: Hashmap size should be 2\n");
    return;
  }

  int lookup = 1;
  if (strcmp(chashmap_get(map, &lookup), "one") != 0) {
    printf("FAILED: Key 1 value incorrect\n");
    return;
  }

  lookup = 1 + NUMBER_BUCKETS;
  if (strcmp(chashmap_get(map, &lookup), "two") != 0) {
    printf("FAILED: Key %d value incorrect\n", 1 + NUMBER_BUCKETS);
    return;
  }

  // check that both keys are in the same bucket
  size_t bucket_index1 = int_hash(key1) % NUMBER_BUCKETS;
  size_t bucket_index2 = int_hash(key2) % NUMBER_BUCKETS;
  if (bucket_index1 != bucket_index2) {
    printf("FAILED: Keys are not in the same bucket\n");
    return;
  }
  // get the underlying clinkedlist for the bucket
  struct CLinkedList *bucket = map->buckets[bucket_index1];
  if (bucket == NULL || clinklist_size(bucket) != 2) {
    printf("FAILED: Bucket does not contain 2 entries\n");
    return;
  }
  chashmap_free(map);
  printf("PASSED test_chashmap_collision\n");
}

void test_chashmap_all() {
  test_chashmap_create();
  test_chashmap_put_and_get();
  test_chashmap_get_nonexistent();
  test_chashmap_put_multiple();
  test_chashmap_put_update();
  test_chashmap_contains();
  test_chashmap_delete();
  test_chashmap_delete_nonexistent();
  test_chashmap_collision();
}

int main() {
  test_chashmap_all();
  return 0;
}
