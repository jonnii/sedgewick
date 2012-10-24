#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "minunit.h"
#include "../src/vector.h"
#include "../src/sorting.h"

#define SORT_RANGE 100

int *test_data(int value)
{
  int *data = malloc(sizeof(int));
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

int compare(void *i, void *j)
{
  return *((int*)i) - *((int*)j);
}

char *test_check_sorted()
{
  vector_p vector = vector_create(sizeof(int)); 
  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));
  vector_add(vector, test_data(2));
  vector_add(vector, test_data(3));
  vector_add(vector, test_data(4));

  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_selection_sort()
{
  vector_p vector = make_vector(); 

  sort_selection(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_insertion_sort()
{
  vector_p vector = make_vector();

  sort_insertion(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_shell_sort()
{
  vector_p vector = make_vector();

  sort_shell(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_merge_sort()
{
  vector_p vector = make_vector();

  sort_merge(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_merge_bu_sort()
{
  vector_p vector = make_vector();

  sort_merge_bu(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_quicksort()
{
  vector_p vector = make_vector();

  sort_quicksort(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_quicksort3()
{
  vector_p vector = make_vector();

  sort_quicksort3(vector, compare);
  mu_assert(check_sorted(vector, compare) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_check_sorted);
  mu_run_test(test_selection_sort);
  mu_run_test(test_insertion_sort);
  mu_run_test(test_shell_sort);
  mu_run_test(test_merge_sort);
  mu_run_test(test_merge_bu_sort);
  mu_run_test(test_quicksort);
  mu_run_test(test_quicksort3);

  return NULL;
}

RUN_TESTS(all_tests);