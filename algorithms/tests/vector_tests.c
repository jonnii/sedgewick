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

  vector_free(vector);
  return NULL;
}

char *test_create_with_capacity()
{
  vector_p vector = vector_create_with_capacity(sizeof(int), 50);
  
  mu_assert(vector->capacity == 50, "should set initial capacity");

  vector_free(vector);
  return NULL;
}

char *test_add()
{
  vector_p vector = vector_create(sizeof(int));
  size_t index = vector_add(vector, test_data(1));

  mu_assert(index == 0, "should have added at index 0");
  mu_assert(vector->length == 1, "expected length 1");

  vector_free(vector);
  return NULL;
}

char *test_add_elements()
{
  vector_p vector = vector_create(sizeof(int));

  size_t i0 = vector_add(vector, test_data(0));
  size_t i1 = vector_add(vector, test_data(1));
  size_t i2 = vector_add(vector, test_data(2));

  mu_assert(*(int*)vector_get(vector, 0) == 0, "expected 0");
  mu_assert(*(int*)vector_get(vector, 1) == 1, "expected 1");
  mu_assert(*(int*)vector_get(vector, 2) == 2, "expected 2");
  mu_assert(i0 == 0, "should have index 0");
  mu_assert(i1 == 1, "should have index 1");
  mu_assert(i2 == 2, "should have index 2");

  vector_free(vector);
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

  vector_free(vector);
  return NULL;
}

char *test_set_copy_retain_policy()
{
  vector_p vector = vector_create(sizeof(int));
  vector_copy_elements(vector);

  mu_assert(vector->create_element != NULL, "didnt set retain policy");
  mu_assert(vector->free_element != NULL, "didnt set release policy");

  vector_free(vector);
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

  vector_free(vector);
  return NULL;
}

char *test_get()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(1));

  int data = *((int*)vector_get(vector, 0));
  mu_assert(data == 1, "expected same value");

  vector_free(vector);
  return NULL;
}

char *test_get_out_of_range()
{
  vector_p vector = vector_create(sizeof(int));
  
  void *data = vector_get(vector, 30);
  mu_assert(data == NULL, "expected value to be null");

  vector_free(vector);
  return NULL;
}

char *test_set()
{
  vector_p vector = vector_create(sizeof(int));

  vector_add(vector, test_data(1));
  int set = vector_set(vector, 0, test_data(2));

  mu_assert(*(int*)vector_get(vector, 0) == 2, "expected 2");
  mu_assert(set, "expected to have set");

  vector_free(vector);
  return NULL;
}

char *test_set_out_of_range()
{
  vector_p vector = vector_create(sizeof(int));

  int set = vector_set(vector, 3500, test_data(2));

  mu_assert(!set, "expected to not have set");

  vector_free(vector);
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

  vector_free(vector);
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

  vector_free(vector);
  return NULL;
}

char *test_remove_and_resize()
{
  vector_p vector = vector_create(sizeof(int));

  for(int i = 0 ; i < 80 ; ++i)
  {
    vector_add(vector, test_data(i));
  }

  for(int i = 0 ; i < 60 ; ++i)
  {
    vector_remove(vector, 0);
  }

  mu_assert(vector->capacity == 20, "should have reduced capacity");

  vector_free(vector);
  return NULL;
}

char *test_remove_out_of_range()
{
  vector_p vector = vector_create(sizeof(int));

  vector_remove(vector, 100);

  mu_assert(vector->length == 0, "should be empty");

  vector_free(vector);
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
  
  vector_free(vector);
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
  
  vector_free(vector);
  return NULL;
}

char *test_copy_shallow()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(0));
  vector_add(vector, test_data(1));

  vector_p copy = vector_copy_shallow(vector);

  mu_assert(vector->length == copy->length, "expected same length for clone");
  mu_assert(*(int*)vector_get(copy, 1) == 1, "expected data to be copied");

  vector_free(copy);
  vector_free(vector);
  return NULL;
}

char *test_iterator()
{
  vector_p vector = vector_create(sizeof(int));
  vector_add(vector, test_data(10));
  vector_add(vector, test_data(20));

  int total = 0;
  int iterations = 0;
  
  iterator_p iterator = vector_iterator(vector);
  while(iterator_next(iterator))
  {
    total += *(int*)iterator->current;
    iterations++;
  }

  mu_assert(total == 30, "should have visited each item in the vector");
  mu_assert(iterations == 2, "should have visited 2 items");

  vector_free(vector);
  return NULL;
}

char *test_iterator_empty()
{
  vector_p vector = vector_create(sizeof(int));
  int iterations = 0;;
  
  iterator_p iterator = vector_iterator(vector);
  while(iterator_next(iterator))
  {
    iterations++;
  }

  mu_assert(iterations == 0, "should not have iterated");

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
  mu_run_test(test_remove_and_resize);
  mu_run_test(test_remove_out_of_range);
  mu_run_test(test_insert_at_beginning);
  mu_run_test(test_insert_at_end);
  mu_run_test(test_copy_shallow);
  mu_run_test(test_iterator);
  mu_run_test(test_iterator_empty);

  return NULL;
}

RUN_TESTS(all_tests);