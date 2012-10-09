#include "minunit.h"
#include <linked_list.h>
#include <assert.h>
#include <string.h>

char *test_truth()
{
	mu_assert(1==0, "The truth will set you free."); 
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_truth);

	return NULL;
}

RUN_TESTS(all_tests);