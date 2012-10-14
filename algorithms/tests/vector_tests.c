#include <assert.h>
#include <string.h>

#include "minunit.h"
#include "../src/vector.h"

int *test_data(int value)
{
  int *data = malloc(sizeof(int));
  *data = value;
  return data;
}

char *test_create()
{
  vector_p vector = vector_create(sizeof(int));

  mu_assert(vector->element_size == sizeof(int), "should have set element size");
  mu_assert(vector->length == 0, "should be empty");
  mu_assert(vector->capacity == 10, "should set initial capacity");
  mu_assert(vector->data != NULL, "data wasn't initialized");
  mu_assert(vector->create_element == NULL, "retain policy was set");
  mu_assert(vector->free_element == NULL, "release policy was set");
  
  for(size_t i = 0 ; i < vector->capacity ; ++i)
  {
    mu_assert(vector->data[i] == NULL, "data wasn't initialized to empty");
  }

  vector_destroy(vector);
  return NULL;
}

char *test_create_with_capacity()
{
  vector_p vector = vector_create_with_capacity(sizeof(int), 50);
  
  mu_assert(vector->capacity == 50, "should set initial capacity");

  vector_destroy(vector);
  return NULL;
}

char *test_add()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(1));

  mu_assert(vector->length == 1, "expected length 1");

  vector_destroy(vector);
  return NULL;
}

char *test_add_elements()
{
  vector_p vector = vector_create(sizeof(int));

  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));
  vector_add(vector, test_data(2));

  mu_assert(*(int*)vector_get(vector, 0) == 0, "expected 0");
  mu_assert(*(int*)vector_get(vector, 1) == 1, "expected 1");
  mu_assert(*(int*)vector_get(vector, 2) == 2, "expected 2");

  vector_destroy(vector);
  return NULL;
}

char *test_add_elements_causing_expand()
{
  vector_p vector = vector_create(sizeof(int));

  for(int i = 0 ; i < 20 ;++i)
  {
    vector_add(vector, test_data(i));
  }

  mu_assert(vector->capacity == 20, "expected capacity of 20");
  mu_assert(*(int*)vector_get(vector, 0) == 0, "expected 0");
  mu_assert(*(int*)vector_get(vector, 19) == 19, "expected 0");

  vector_destroy(vector);
  return NULL;
}

char *test_set_copy_retain_policy()
{
  vector_p vector = vector_create(sizeof(int));
  vector_copy_elements(vector);

  mu_assert(vector->create_element != NULL, "didnt set retain policy");
  mu_assert(vector->free_element != NULL, "didnt set release policy");

  vector_destroy(vector);
  return NULL;
}

char *test_add_with_retain_policy()
{
  vector_p vector = vector_create(sizeof(int));
  vector_copy_elements(vector);

  int *original = test_data(1);
  vector_add(vector, original);
  int *got = (int*)vector_get(vector, 0);

  mu_assert(*got == 1, "expected same value");
  mu_assert(got != original, "shouldn't get same data back");

  vector_destroy(vector);
  
  return NULL;
}

char *test_get()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(1));

  int data = *((int*)vector_get(vector, 0));
  mu_assert(data == 1, "expected same value");

  vector_destroy(vector);
  return NULL;
}

char *test_get_out_of_range()
{
  vector_p vector = vector_create(sizeof(int));
  
  void *data = vector_get(vector, 30);
  mu_assert(data == NULL, "expected value to be null");

  vector_destroy(vector);
  return NULL;
}

char *test_set()
{
  vector_p vector = vector_create(sizeof(int));

  vector_add(vector, test_data(1));
  int set = vector_set(vector, 0, test_data(2));

  mu_assert(*(int*)vector_get(vector, 0) == 2, "expected 2");
  mu_assert(set, "expected to have set");

  vector_destroy(vector);
  return NULL;
}

char *test_set_out_of_range()
{
  vector_p vector = vector_create(sizeof(int));

  int set = vector_set(vector, 3500, test_data(2));

  mu_assert(!set, "expected to not have set");

  vector_destroy(vector);
  return NULL;
}

char *test_swap()
{
  vector_p vector = vector_create(sizeof(int));

  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));

  int swapped = vector_swap(vector, 0, 1);

  mu_assert(swapped, "expected to have swapped");
  mu_assert(*(int*)vector_get(vector, 0) == 1, "expected 1");
  mu_assert(*(int*)vector_get(vector, 1) == 0, "expected 0");

  vector_destroy(vector);
  return NULL;
}

char *test_remove()
{
  vector_p vector = vector_create(sizeof(int));

  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));
  vector_add(vector, test_data(2));

  vector_remove(vector, 1);

  mu_assert(vector->length == 2, "should have a length of 2");
  mu_assert(*(int*)vector_get(vector, 1) == 2, "should have removed item");

  vector_destroy(vector);
  return NULL;
}

char *test_remove_out_of_range()
{
  vector_p vector = vector_create(sizeof(int));

  vector_remove(vector, 100);

  mu_assert(vector->length == 0, "should be empty");

  vector_destroy(vector);
  return NULL;
}

char *test_insert_at_beginning()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(1));

  int did_insert = vector_insert(vector, 0, test_data(0));

  mu_assert(vector->length == 2, "should have a length of 2");
  mu_assert(did_insert, "should have inserted");
  mu_assert(*(int*)vector_get(vector, 0) == 0, "should have added item at start");
  mu_assert(*(int*)vector_get(vector, 1) == 1, "should have moved other items");
  
  vector_destroy(vector);
  return NULL;
}

char *test_insert_at_end()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));

  int did_insert = vector_insert(vector, 2, test_data(2));

  mu_assert(vector->length == 3, "should have a length of 3");
  mu_assert(did_insert, "should have inserted");
  mu_assert(*(int*)vector_get(vector, 2) == 2, "should have added item at end");
  
  vector_destroy(vector);
  return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_create_with_capacity);
  mu_run_test(test_add);
  mu_run_test(test_add_elements);
  mu_run_test(test_add_elements_causing_expand);
  mu_run_test(test_set_copy_retain_policy);
  mu_run_test(test_add_with_retain_policy);
  mu_run_test(test_get);
  mu_run_test(test_set);
  mu_run_test(test_set_out_of_range);
  mu_run_test(test_swap);
  mu_run_test(test_remove);
  mu_run_test(test_remove_out_of_range);
  mu_run_test(test_insert_at_beginning);
  mu_run_test(test_insert_at_end);

  return NULL;
}

RUN_TESTS(all_tests);