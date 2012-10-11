#include "minunit.h"
#include <linked_list.h>
#include <assert.h>
#include <string.h>

int *make_test_data(int value)
{
	int *data = malloc(sizeof(int));
	*data = value;
	return data;
}

List *create_list_with_items(int numItems)
{
	List *list = List_create();
	for(int i = 0 ; i < numItems ; ++i)
	{
		List_add(list, make_test_data(i));
	}
	return list;
}

char *test_create()
{
	List *list = List_create();
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
	void *data = make_test_data(1);
	List_add(list, data);

	mu_assert(list->first != NULL, "first item in list not set");
	mu_assert(list->first->value != NULL, "first list value not set");
	mu_assert(list->first->value == data, "Did not set data correctly");

	List_clear_and_destroy(list);
	return NULL;
}

char *test_add_multiple()
{
	List *list = List_create();
	void *data = make_test_data(1);
	List_add(list, make_test_data(2));
	List_add(list, data);

	mu_assert(list->first->next->value == data, "Did not set data correctly");

	List_clear_and_destroy(list);
	return NULL;	
}

char *test_find_at_index_on_empty_list()
{
	List *list = List_create();

	void *data = List_find_index(list, 0);

	mu_assert(data == NULL, "should have returned null data");

	List_clear_and_destroy(list);
	return NULL;
}

char *test_find_at_index()
{
	List *list = create_list_with_items(5);

	int second = *((int*)List_find_index(list, 2));
	mu_assert(second == 2, "didn't find the right value");

	int third = *((int*)List_find_index(list, 3));
	mu_assert(third == 3, "didn't find the right value");

	List_clear_and_destroy(list);

	return NULL;
}

char *test_find_index_greater_than_list_size()
{
	List *list = create_list_with_items(5);

	void *second = List_find_index(list, 10);
	mu_assert(second == NULL, "should not have found a value");

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
	List_add(list, make_test_data(1));

	List_clear(list);

	mu_assert(list->first->value == NULL, "The first item is still assigned");

	List_destroy(list);

	return NULL;
}

char *test_clear_and_destroy()
{
	List *list = List_create();
	List_add(list, make_test_data(1));

	List_clear_and_destroy(list);

	return NULL;
}

char *test_count_empty()
{
	List *list = List_create();

	int count = List_count(list);
	mu_assert(count == 0, "should not have any count")

	List_clear_and_destroy(list);

	return NULL;
}

char *test_count()
{
	List *list = create_list_with_items(10);

	int count = List_count(list);
	mu_assert(count == 10, "should have count of 10")

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
	mu_run_test(test_add_multiple);
	mu_run_test(test_find_at_index);
	mu_run_test(test_find_at_index_on_empty_list);
	mu_run_test(test_find_index_greater_than_list_size);
	mu_run_test(test_count_empty);
	mu_run_test(test_count);

	return NULL;
}

RUN_TESTS(all_tests);