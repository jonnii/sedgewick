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

#endif