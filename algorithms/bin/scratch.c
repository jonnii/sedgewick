#include <stdio.h>
#include <stdlib.h>
#include "../src/vector.h"
#include "../src/quicksort.h"

int *test_data(int value)
{
  int *data = malloc(sizeof(int));
  *data = value;
  return data;
}

int qscompare(const void *i, const void *j)
{
  return **((int**)i) - **((int**)j);
}

int main()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(4));
  vector_add(vector, test_data(1));
  vector_add(vector, test_data(2));
  vector_add(vector, test_data(3));

  qsort(vector->data, vector->length, sizeof(void*), qscompare);
  
  for(size_t i = 0 ; i < vector->length ; i++)
  {
    int k = *(int*) vector_get(vector, i);
    printf("%d\n", k);
  }

  vector_free(vector);
  
  return 0;
}