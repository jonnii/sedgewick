#include "minunit.h"
#include <vector.h>
#include <assert.h>
#include <string.h>

int *make_test_data(int value)
{
  int *data = malloc(sizeof(int));
  *data = value;
  return data;
}

char *test_create()
{
  vector_p vector = vector_create();
  
  mu_assert(vector->length == 0, "should be empty");
  mu_assert(vector->capacity == 10, "should set initial capacity");
  mu_assert(vector->data != NULL, "data wasn't initialized");
  mu_assert(vector->retain_policy == NULL, "retain policy was set");
  mu_assert(vector->release_policy == NULL, "release policiy was set");
    
  for(size_t i = 0 ; i < vector->capacity ; ++i)
  {
    mu_assert(vector->data[i] == NULL, "data wasn't initialized to empty");
  }

  vector_destroy(vector);
  return NULL;
}

char *test_create_with_capacity()
{
  vector_p vector = vector_create_with_capacity(50);
  
  mu_assert(vector->capacity == 50, "should set initial capacity");

  vector_destroy(vector);
  return NULL;
}

char *test_add()
{
  vector_p vector = vector_create();
  vector_add(vector, make_test_data(1));

  mu_assert(vector->length == 1, "expected length 1");

  vector_destroy(vector);
  return NULL;
}

char *test_add_with_retain_policy()
{
  vector_p vector = vector_create();

  int *original = make_test_data(1);
  vector_add(vector, original);
  int *got = (int*)vector_get(vector, 0);

  mu_assert(*got == 1, "expected same value");
  //mu_assert(got != original, "shouldn't get same data back");

  vector_destroy(vector);
  
  return NULL;
}

char *test_get()
{
  vector_p vector = vector_create();
  vector_add(vector, make_test_data(1));

  int data = *((int*)vector_get(vector, 0));
  mu_assert(data == 1, "expected same value");

  vector_destroy(vector);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_create_with_capacity);
  mu_run_test(test_add);
  mu_run_test(test_add_with_retain_policy);
  mu_run_test(test_get);

  return NULL;
}

RUN_TESTS(all_tests);