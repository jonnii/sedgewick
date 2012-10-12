#include "vector.h"
#include <stdlib.h>

vector_p vector_create_with_capacity(int capacity)
{
  vector_p vector = calloc(1, sizeof(struct vector));

  vector->capacity = capacity;
  vector->data = calloc(capacity, sizeof(void*));
  vector->retain_policy = NULL;
  vector->release_policy = NULL;

  return vector;
}

vector_p vector_create()
{
  return vector_create_with_capacity(10);
}

void vector_destroy(vector_p vector)
{
  free(vector->data);
  free(vector);
}

void vector_copy_retain_policy(vector_p vector, retain_release_p policy)
{
  vector->retain_policy = policy;
  vector->release_policy = free; 
}

void vector_add(vector_p vector, void *data)
{
  void *element = data;
  if(vector->retain_policy != NULL) {
    element = vector->retain_policy(element);
  }

  int offset = vector->length;
  vector->data[offset] = element;
  vector->length++;
}

void *vector_get(vector_p vector, size_t index)
{
  return vector->data[index];
}