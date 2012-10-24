#include "test_helpers.h"
#include "../src/priority_queue.h"

char *test_create()
{
	priority_queue_p queue = priority_queue_create(sizeof(int), compare_intp);	
	
	mu_assert(queue != NULL, "should have created queue");
	mu_assert(queue->vector != NULL, "should have created vector");
	mu_assert(queue->comparator != NULL, "should have set comparator");

	priority_queue_free(queue);
	return NULL;
}

char *test_insert()
{
	priority_queue_p queue = priority_queue_create(sizeof(int), compare_intp);	

	priority_queue_insert(queue, test_data(10));
	mu_assert(*(int*)vector_get(queue->vector, 0) == 10, "should have set first item");	

	priority_queue_free(queue);
	return NULL;
}

char *test_insert_then_swim()
{
	priority_queue_p queue = priority_queue_create(sizeof(int), compare_intp);	

	priority_queue_insert(queue, test_data(10));
	priority_queue_insert(queue, test_data(20));
	mu_assert(*(int*)vector_get(queue->vector, 0) == 10, "should have set first item");	

	priority_queue_free(queue);
	return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_insert);
  mu_run_test(test_insert_then_swim);

  return NULL;
}

RUN_TESTS(all_tests);