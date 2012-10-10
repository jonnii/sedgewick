#include "minunit.h"
#include <linked_list.h>
#include <assert.h>
#include <string.h>

int *make_test_data()
{
	int *data = malloc(sizeof(int));
	*data = 6;
	return data;
}

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

char *test_add()
{
	List *list = List_create();
	void *data = make_test_data();
	List_add(list, data);

	mu_assert(list->first != NULL, "first item in list not set");
	mu_assert(list->first->value != NULL, "first list value not set");
	mu_assert(list->first->value == data, "Did not set data correctly");

	List_clear_and_destroy(list);
	return NULL;
}

char *test_clear_empty()
{
	List *list = List_create();

	List_clear(list);

	return NULL;
}

char *test_clear()
{
	List *list = List_create();
	List_add(list, make_test_data());

	List_clear(list);

	mu_assert(list->first->value == NULL, "The first item is still assigned");

	List_destroy(list);

	return NULL;
}

char *test_clear_and_destroy()
{
	List *list = List_create();
	List_add(list, make_test_data());

	List_clear_and_destroy(list);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_destroy);
	mu_run_test(test_add);
	mu_run_test(test_clear_empty);
	mu_run_test(test_clear);
	mu_run_test(test_clear_and_destroy);

	return NULL;
}

RUN_TESTS(all_tests);