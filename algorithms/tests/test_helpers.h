#ifndef _test_helpers_h
#define _test_helpers_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "minunit.h"
#include "../src/vector.h"

#define SORT_RANGE 100

int *test_data(int value)
{
  int *data = (int*)malloc(sizeof(int));
  *data = value;
  return data;
}

vector_p make_vector()
{
  vector_p vector = vector_create(sizeof(int));
  for(int i = 0 ; i < SORT_RANGE ; i++)
  {
    int random = rand() % SORT_RANGE;
    vector_add(vector, test_data(random));
  }
  return vector;
}

vector_p make_vector_of_size(size_t size)
{
  vector_p vector = vector_create(sizeof(int));
  for(size_t i = 0 ; i < size ; i++)
  {
    int random = rand() % size;
    vector_add(vector, test_data(random));
  }
  return vector;
}

vector_p make_sorted(size_t size)
{
  vector_p vector = vector_create(sizeof(int));
  for(size_t i = 0 ; i < size ; i++)
  {
    vector_add(vector, test_data(i));
  }
  return vector;
}

vector_p make_reverse_sorted(size_t size)
{
  vector_p vector = vector_create(sizeof(int));
  for(size_t i = size ; i > 0 ; i--)
  {
    vector_add(vector, test_data(i));
  }
  return vector;
}

#endif