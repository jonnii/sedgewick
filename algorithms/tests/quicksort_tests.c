#include "test_helpers.h"
#include "../src/sorting.h"
#include "../src/quicksort.h"

char *test_quicksort_already_sorted()
{
  vector_p vector = make_sorted(3);

  quicksort(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_quicksort_reverse_sorted()
{
  vector_p vector = make_reverse_sorted(3);

  quicksort(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_quicksort_small()
{
  vector_p vector = make_vector_of_size(20);

  quicksort(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_quicksort()
{
  vector_p vector = make_vector();

  quicksort(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_quicksort3()
{
  vector_p vector = make_vector();

  quicksort3(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *test_quicksortp()
{
  vector_p vector = make_vector();

  quicksortp(vector, compare_intp);
  mu_assert(check_sorted(vector, compare_intp) == 1, "should have been sorted");

  vector_free(vector);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_quicksort_already_sorted);
  mu_run_test(test_quicksort_reverse_sorted);
  mu_run_test(test_quicksort_small);

  mu_run_test(test_quicksort);
  mu_run_test(test_quicksort3);
  mu_run_test(test_quicksortp);

  return NULL;
}

RUN_TESTS(all_tests);