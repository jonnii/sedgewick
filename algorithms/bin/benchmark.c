#include <stdio.h>
#include <string.h>
#include "../src/sorting.h"
#include "../src/vector.h"

int *test_data(int value)
{
  int *data = malloc(sizeof(int));
  *data = value;
  return data;
}

vector_p make_vector(int num_items)
{
  vector_p vector = vector_create(sizeof(int));
  for(int i = 0 ; i < num_items ; i++)
  {
    int random = rand() % num_items;
    vector_add(vector, test_data(random));
  }
  return vector;
}

sorter_p make_sorter(char *name)
{
  if(strncmp(name, "merge", 5) == 0)
  {
    return sort_merge;
  }
  if(strncmp(name, "quick", 5) == 0)
  {
    return sort_quicksort;
  }
  else
  {
    return NULL;
  }
}

int main(int argc, char *argv[])
{
  printf("benchmark\n");
  int num_elements = atoi(argv[1]);
  printf("running %s with %d elements\n", argv[2], num_elements);

  vector_p vector = make_vector(num_elements);
  sorter_p sorter = make_sorter(argv[2]);
  
  if(sorter == NULL)
  {
    printf("could not find a sorter for %s\n", argv[2]);
  }

  sorter(vector, compare_intp);

  vector_destroy(vector);
  return 0;
}