#include "vector.h"

vector_p vector_create_with_capacity(int capacity)
{
	vector_p vector = calloc(1, sizeof(struct vector));
	vector->capacity = capacity;
	return vector;
}

vector_p vector_create()
{
  return vector_create_with_capacity(10);
}