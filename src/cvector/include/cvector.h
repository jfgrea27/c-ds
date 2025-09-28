#ifndef CVECTOR_H
#define CVECTOR_H

#include <stddef.h>

#define INITIAL_CAPACITY 4

struct CVector {
  void **data;
  size_t size;
  size_t capacity;
};

struct CVector *cvector_create();

/*
    Free the memory allocated for the vector.

    @param vec The vector to free.
*/
void cvector_free(struct CVector *vec);

/*
    Add an item to the end of the vector.

    @param vec The vector to add the item to.
    @param item The item to add.
*/
void cvector_push(struct CVector *vec, void *item);

/*
    Get an item from the vector by index.

    @param vec The vector to get the item from.
    @param index The index of the item to get.

    @return The item at the index.
*/
void *cvector_get(struct CVector *vec, size_t index);

/*
    Set an item in the vector by index.

    @param vec The vector to set the item in.
    @param index The index of the item to set.
    @param item The item to set.
*/
void cvector_set(struct CVector *vec, size_t index, void *item);

/*
    Delete an item from the vector by index.

    @param vec The vector to delete the item from.
    @param index The index of the item to delete.
*/
void cvector_delete(struct CVector *vec, size_t index);

/*
    Double the capacity of the vector if it is full.
    
    @param vec The vector to double the capacity of.
*/
void maybe_double_capacity(struct CVector *vec);

/*
    Get the size of the vector.

    @param vec The vector to get the size of.
*/
size_t cvector_size(struct CVector *vec);

#endif