# C Data Structures

This repository includes a library of data structures implemented in C from scratch, including:

- [cvector](#cvector): a dynamic array of pointers.
- cbtree: TODO

## Repository structure

The repository is organized with each DS holding its own directory (module).

## Setup

This repository relies on [Nix Flakes](https://nixos.wiki/wiki/Flakes) and [direnv](https://direnv.net/).
Just `cd` into this repository if you have both setup and it will setup your `devShell` for you.

## Testing

To run a test on a datastructure, run the following:

```sh
# specific test
just run-test NAME_DS
# all tests
just run-tests
```

## Memory leaks

`valgrind` is used to check against any memory leaks on the libraries throught **integration tests**. Please run the following to get a full report:

```sh
# specific memory check
just mem-check NAME_DS
```


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

Notes:
- Elements should be heaped; `CVector` does not allow adding stack elements.
- Elements can be added, updated, deleted.
- Whenever `CVector` is full (a.k.a. `CVector.size` == `CVector.capacity`), we `realloc` the heap memory holding the pointers to the underlining elements and double its size.

A full example of the `CVector` API in action can be seen in `src/cvector/main.c`.

