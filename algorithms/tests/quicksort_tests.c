
#include "test_helpers.h"
#include "../src/quicksort.h"

char *test_quicksort()
{
  vector_p vector = make_vector();

  quicksort(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *test_quicksort3()
{
  vector_p vector = make_vector();

  quicksort3(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_destroy(vector);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_quicksort);
  mu_run_test(test_quicksort3);

  return NULL;
}

RUN_TESTS(all_tests);