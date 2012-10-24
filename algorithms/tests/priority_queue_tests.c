#include "test_helpers.h"
#include "../src/priority_queue.h"

char *test_create()
{
	priority_queue_p queue = priority_queue_create(sizeof(int));	
	
	mu_assert(queue != NULL, "should have created queue");
	mu_assert(queue->vector != NULL, "should have created vector");

	return NULL;
}

char *test_free()
{
	priority_queue_p queue = priority_queue_create(sizeof(int));	
	priority_queue_free(queue);
	return NULL;
}

char *all_tests()
{
  mu_suite_start();

  mu_run_test(test_create);
  mu_run_test(test_free);
  
  return NULL;
}

RUN_TESTS(all_tests);