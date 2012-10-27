#include <stdio.h>
#include <string.h>
#include "../src/sorting.h"
#include "../src/quicksort.h"
#include "../src/vector.h"

#include <sys/time.h>
#include <sys/resource.h>

#define RUNS 100

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
  if(strncmp(name, "quickp", 6) == 0)
  {
    return quicksortp;
  }
  return NULL;
}

void benchmark_one(vector_p vector, char *sorter_name)
{
  sorter_p sorter = make_sorter(sorter_name);
  if(sorter == NULL)
  {
    printf("could not find a sorter for %s\n", sorter_name);
    return;
  }

  float totalRunningTime = 0;
  for(int i = 0 ; i < RUNS ; ++i)
  {
    vector_p copy = vector_copy_shallow(vector);
    
    double startedAt = get_time();
    sorter(copy, compare_intp);
    double finishedAt = get_time();

    totalRunningTime += (finishedAt - startedAt);
    
    if(!check_sorted(copy, compare_intp))
    {
      printf("not sorted\n");
      return;
    }

    vector_free(copy);
  }

  float averageRunningTime = totalRunningTime / RUNS;
  printf("%s\taverage %fms\n", sorter_name, averageRunningTime);
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
  printf("running %s with %d elements %d runs\n", argv[2], num_elements, RUNS);

  vector_p vector = make_vector(num_elements);
  if(strncmp(argv[2], "all", 3) == 0)
  {
    benchmark_one(vector, "quick");
    benchmark_one(vector, "quick3");
    benchmark_one(vector, "quickp");
    benchmark_one(vector, "merge");
  }
  else
  {
    benchmark_one(vector, argv[2]);
  }

  vector_free(vector);
  return 0;
}