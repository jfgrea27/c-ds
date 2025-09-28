# C Data Structures

This repository includes a library of data structures implemented in C from scratch, including:

- [cvector](#cvector): a dynamic array of pointers.
- cbtree: TODO

## Design of each data structure

### cvector

`CVector` defined below

```c
typedef struct {
  void **data;
  size_t size;
  size_t capacity;
} CVector;
```

holds an array of pointers on the heap. This allows for allocation of any data type.

Elements of the array can be added, updated, deleted.

Whenever `CVector` is full (a.k.a. `CVector.size` == `CVector.capacity`), we `realloc` the heap memory holding the pointers to the underlining elements and double its size.

This allows for a dynamic allocation of memory given `CVector`'s caller.
