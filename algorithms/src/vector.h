#ifndef _vector_h
#define _vector_h

#include <stdlib.h>

struct vector {
  size_t length;
  size_t capacity;
  void **data;

  void *(*retain_policy)(void*);
  void (*release_policy)(void*);
};

typedef struct vector* vector_p;

vector_p vector_create();

vector_p vector_create_with_capacity(int capacity);

void vector_destroy(vector_p vector);

void vector_add(vector_p vector, void *data);

void *vector_get(vector_p vector, size_t index);

#endif