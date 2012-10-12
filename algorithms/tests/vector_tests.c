#include "minunit.h"
#include <vector.h>
#include <assert.h>
#include <string.h>

char *test_create()
{
  vector_p vector = vector_create();
  
  mu_assert(vector->length == 0, "should be empty");
  mu_assert(vector->capacity == 10, "should set initial capacity");

  return NULL;
}

char *test_create_with_capacity()
{
  vector_p vector = vector_create_with_capacity(50);
  
  mu_assert(vector->capacity == 50, "should set initial capacity");

  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);

  return NULL;
}

RUN_TESTS(all_tests);