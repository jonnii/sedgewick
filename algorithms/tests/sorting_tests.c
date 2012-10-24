#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "test_helpers.h"
#include "../src/vector.h"
#include "../src/sorting.h"

char *test_check_sorted()
{
  vector_p vector = vector_create(sizeof(int)); 
  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));
  vector_add(vector, test_data(2));
  vector_add(vector, test_data(3));
  vector_add(vector, test_data(4));

  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_selection_sort()
{
  vector_p vector = make_vector(); 

  sort_selection(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_insertion_sort()
{
  vector_p vector = make_vector();

  sort_insertion(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_shell_sort()
{
  vector_p vector = make_vector();

  sort_shell(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_merge_sort()
{
  vector_p vector = make_vector();

  sort_merge(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_merge_bu_sort()
{
  vector_p vector = make_vector();

  sort_merge_bu(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
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

  return NULL;
}

RUN_TESTS(all_tests);