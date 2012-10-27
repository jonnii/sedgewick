#include <stdio.h>
#include "../src/vector.h"
#include "../src/quicksort.h"

int *test_data(int value)
{
  int *data = malloc(sizeof(int));
  *data = value;
  return data;
}

int main()
{
  vector_p vector = vector_create(sizeof(int));
  
  vector_add(vector, test_data(70));
  vector_add(vector, test_data(60));
  vector_add(vector, test_data(50));
  vector_add(vector, test_data(40));
  vector_add(vector, test_data(30));
  vector_add(vector, test_data(20));
  vector_add(vector, test_data(10));

  vector_add(vector, test_data(120));
  vector_add(vector, test_data(110));
  vector_add(vector, test_data(100));
  vector_add(vector, test_data(90));
  vector_add(vector, test_data(80));
  
  vector_add(vector, test_data(40));
  vector_add(vector, test_data(30));
  vector_add(vector, test_data(20));
  vector_add(vector, test_data(10));
  
  vector_add(vector, test_data(40));
  vector_add(vector, test_data(30));
  vector_add(vector, test_data(20));
  vector_add(vector, test_data(10));
  

  quicksort(vector, compare_intp);

  for(size_t i = 0 ; i < vector->length ; i++)
  {
    printf("%d\n", *(int*) vector_get(vector, i));
  }

  vector_free(vector);
  
  return 0;
}