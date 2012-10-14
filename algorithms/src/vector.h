#ifndef _vector_h
#define _vector_h

#include <stdlib.h>

struct vector {
  size_t length;
  size_t capacity;
  size_t element_size;
  void **data;

  void *(*create_element)(struct vector *vector, void*);
  void (*free_element)(void*);
};

typedef struct vector* vector_p;

typedef void *(*retain_release_p)(struct vector *vector, void *data);

vector_p vector_create(size_t element_size);

vector_p vector_create_with_capacity(size_t element_size, int capacity);

void vector_copy_elements(vector_p vector);

void vector_destroy(vector_p vector);

void vector_add(vector_p vector, void *data);

void *vector_get(vector_p vector, size_t index);

int vector_set(vector_p, size_t index, void *data);

//int vector_insert(vector_p, size_t index, void *data);

//void vector_remove(vector_p vector, size_t index);

//void vector_swap(vector_p vector, int i, int j);

#endif