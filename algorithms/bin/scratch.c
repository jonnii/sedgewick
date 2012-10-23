#include <stdio.h>
#include "../src/vector.h"

int *test_data(int value)
{
  int *data = malloc(sizeof(int));
  *data = value;
  return data;
}

int main()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(10));
  vector_add(vector, test_data(20));

  int total = 0;
  int iterations = 0;
  
  iterator_p iterator = vector_iterator(vector);
  while(iterator_next(iterator))
  {
    total += *(int*)iterator->current;
    iterations++;
  }
  
  printf("%d\n", iterations);
  printf("%d\n", total);
  
  return 0;
}