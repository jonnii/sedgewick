#include <stdio.h>
#include <string.h>
#include "../src/sorting.h"
#include "../src/quicksort.h"
#include "../src/vector.h"

#include <sys/time.h>
#include <sys/resource.h>

double get_time()
{
    struct timeval t;
    struct timezone tzp;
    gettimeofday(&t, &tzp);
    return t.tv_sec + t.tv_usec*1e-6;
}

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
  if(strncmp(name, "mergebu", 7) == 0)
  {
    return sort_merge_bu;
  }
  if(strncmp(name, "quick", 5) == 0)
  {
    return quicksort;
  }
  if(strncmp(name, "quick3", 6) == 0)
  {
    return quicksort3;
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    printf("usage: benchmark <iterations> <method>\n");
    return 1;
  }

  printf("benchmark\n");
  int num_elements = atoi(argv[1]);
  printf("running %s with %d elements\n", argv[2], num_elements);

  vector_p vector = make_vector(num_elements);
  sorter_p sorter = make_sorter(argv[2]);
  
  if(sorter == NULL)
  {
    printf("could not find a sorter for %s\n", argv[2]);
  }

  int runs = 10;
  float totalRunningTime = 0;
  for(int i = 0 ; i < runs ; ++i)
  {
    vector_p copy = vector_copy_shallow(vector);
    
    double startedAt = get_time();
    sorter(copy, compare_intp);
    double finishedAt = get_time();

    totalRunningTime += (finishedAt - startedAt);
    
    if(!check_sorted(copy, compare_intp))
    {
      printf("not sorted\n");
      return 1;
    }

    vector_free(copy);
  }

  float averageRunningTime = totalRunningTime / runs;
  printf("total running time %fms\n", totalRunningTime);
  printf("average running time %fms over %d runs\n", averageRunningTime, runs);

  vector_free(vector);
  return 0;
}