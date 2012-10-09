#include "minunit.h"
#include <linked_list.h>
#include <assert.h>
#include <string.h>

char *test_create()
{
	struct List* list = List_create();
	mu_assert(list != NULL, "Could not create list");
	return NULL;
}

char *test_destroy()
{
	List_destroy(List_create());
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);

	return NULL;
}

RUN_TESTS(all_tests);