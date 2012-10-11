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

LinkedList *create_list_with_items(int numItems)
{
	LinkedList *list = LinkedList_create();
	
	for(int i = 0 ; i < numItems ; ++i)
	{
		LinkedList_add(list, make_test_data(i));
	}

	return list;
}

char *test_create()
{
	LinkedList *list = LinkedList_create();
	mu_assert(list != NULL, "Could not create list");
	return NULL;
}

char *test_destroy()
{
	LinkedList_destroy(LinkedList_create());
	return NULL;
}

char *test_add()
{
	LinkedList *list = LinkedList_create();
	void *data = make_test_data(1);
	LinkedList_add(list, data);

	mu_assert(list->first != NULL, "first item in list not set");
	mu_assert(list->first->value != NULL, "first list value not set");
	mu_assert(list->first->value == data, "Did not set data correctly");

	LinkedList_clear_and_destroy(list);
	return NULL;
}

char *test_add_multiple()
{
	LinkedList *list = LinkedList_create();
	void *data = make_test_data(1);
	LinkedList_add(list, make_test_data(2));
	LinkedList_add(list, data);

	mu_assert(list->first->next->value == data, "Did not set data correctly");

	LinkedList_clear_and_destroy(list);
	return NULL;	
}

char *test_find_at_index_on_empty_list()
{
	LinkedList *list = LinkedList_create();

	void *data = LinkedList_find_at(list, 0);

	mu_assert(data == NULL, "should have returned null data");

	LinkedList_clear_and_destroy(list);
	return NULL;
}

char *test_find_at_index()
{
	LinkedList *list = create_list_with_items(5);

	int second = *((int*)LinkedList_find_at(list, 2));
	mu_assert(second == 2, "didn't find the right value");

	int third = *((int*)LinkedList_find_at(list, 3));
	mu_assert(third == 3, "didn't find the right value");

	LinkedList_clear_and_destroy(list);

	return NULL;
}

char *test_find_index_greater_than_list_size()
{
	LinkedList *list = create_list_with_items(5);

	void *second = LinkedList_find_at(list, 10);
	mu_assert(second == NULL, "should not have found a value");

	LinkedList_clear_and_destroy(list);

	return NULL;
}

char *test_clear_empty()
{
	LinkedList *list = LinkedList_create();

	LinkedList_clear(list);
	
	return NULL;
}

char *test_clear()
{
	LinkedList *list = LinkedList_create();
	LinkedList_add(list, make_test_data(1));

	LinkedList_clear(list);

	mu_assert(list->first->value == NULL, "The first item is still assigned");

	LinkedList_destroy(list);

	return NULL;
}

char *test_clear_and_destroy()
{
	LinkedList *list = LinkedList_create();
	LinkedList_add(list, make_test_data(1));

	LinkedList_clear_and_destroy(list);

	return NULL;
}

char *test_count_empty()
{
	LinkedList *list = LinkedList_create();

	int count = LinkedList_count(list);
	mu_assert(count == 0, "should not have any count")

	LinkedList_clear_and_destroy(list);

	return NULL;
}

char *test_count()
{
	LinkedList *list = create_list_with_items(10);

	int count = LinkedList_count(list);
	mu_assert(count == 10, "should have count of 10")

	LinkedList_clear_and_destroy(list);

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