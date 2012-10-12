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

list_p create_list_with_items(int numItems)
{
	list_p list = list_create();
	
	for(int i = 0 ; i < numItems ; ++i)
	{
		list_add(list, make_test_data(i));
	}

	return list;
}

char *test_create()
{
	list_p list = list_create();

	mu_assert(list != NULL, "Could not create list");
	mu_assert(list->length == 0, "length should be 0")

	return NULL;
}

char *test_destroy()
{
	list_destroy(list_create());
	return NULL;
}

char *test_add()
{
	list_p list = list_create();
	void *data = make_test_data(1);
	list_add(list, data);

	mu_assert(list->first != NULL, "first item in list not set");
	mu_assert(list->first->value != NULL, "first list value not set");
	mu_assert(list->first->value == data, "Did not set data correctly");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_add_multiple()
{
	list_p list = list_create();
	void *data = make_test_data(1);
	list_add(list, make_test_data(2));
	list_add(list, data);

	mu_assert(list->first->next->value == data, "Did not set data correctly");

	list_clear_and_destroy(list);
	return NULL;	
}

char *test_find_at_index_on_empty_list()
{
	list_p list = list_create();

	void *data = list_find_at(list, 0);

	mu_assert(data == NULL, "should have returned null data");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_find_at_index()
{
	list_p list = create_list_with_items(5);

	int second = *((int*)list_find_at(list, 2));
	mu_assert(second == 2, "didn't find the right value");

	int third = *((int*)list_find_at(list, 3));
	mu_assert(third == 3, "didn't find the right value");

	list_clear_and_destroy(list);

	return NULL;
}

char *test_find_index_greater_than_list_size()
{
	list_p list = create_list_with_items(5);

	void *second = list_find_at(list, 10);
	mu_assert(second == NULL, "should not have found a value");

	list_clear_and_destroy(list);

	return NULL;
}

char *test_clear_empty()
{
	list_p list = list_create();

	list_clear(list);
	
	mu_assert(list->length == 0, "list should be empty");

	return NULL;
}

char *test_clear()
{
	list_p list = list_create();
	list_add(list, make_test_data(1));

	list_clear(list);

	mu_assert(list->first->value == NULL, "The first item is still assigned");
	mu_assert(list->length == 0, "list should be empty");

	list_destroy(list);
	return NULL;
}

char *test_clear_and_destroy()
{
	list_p list = list_create();
	list_add(list, make_test_data(1));

	list_clear_and_destroy(list);

	return NULL;
}

char *test_length_empty()
{
	list_p list = list_create();

	mu_assert(list->length == 0, "should not have any length")

	list_clear_and_destroy(list);
	return NULL;
}

char *test_length()
{
	list_p list = create_list_with_items(10);

	mu_assert(list->length == 10, "should have length of 10")

	list_clear_and_destroy(list);
	return NULL;
}

char *test_delete_at_empty()
{
	list_p list = list_create();

	list_delete_at(list, 0);
	mu_assert(list->length == 0, "didnt find correct length");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_delete_at_start()
{
	list_p list = create_list_with_items(3);

	list_delete_at(list, 0);

	int value = *((int*)list_find_at(list, 0));
	mu_assert(value == 1, "didn't find the right value");	
	mu_assert(list->length == 2, "didnt find correct length");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_delete_at_middle()
{
	list_p list = create_list_with_items(8);

	list_delete_at(list, 4);

	int value = *((int*)list_find_at(list, 4));
	mu_assert(value == 5, "didn't find the right value");	
	mu_assert(list->length == 7, "didnt find correct length");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_delete_at_end()
{
	list_p list = create_list_with_items(8);

	list_delete_at(list, 7);

	mu_assert(list->length == 7, "didnt find correct length");
	mu_assert(list_find_at(list, 7) == NULL, "had value at 7th place");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_delete_at_after()
{
	list_p list = create_list_with_items(8);

	list_delete_at(list, 10);

	list_clear_and_destroy(list);
	return NULL;
}

char *test_index_of_not_found()
{
	list_p list = create_list_with_items(8);	

	int index = list_index_of(list, make_test_data(5000));
	mu_assert(index == -1, "expected -1 when index of not found");

	list_clear_and_destroy(list);
	return NULL;
}

char *test_index_of()
{
	list_p list = create_list_with_items(5);
	void *data = make_test_data(30);
	list_add(list, data);

	int index = list_index_of(list, data);
	mu_assert(index == 5, "didnt find correct index");

	list_clear_and_destroy(list);
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
	mu_run_test(test_length_empty);
	mu_run_test(test_length);
	mu_run_test(test_delete_at_empty);
	mu_run_test(test_delete_at_start);
	mu_run_test(test_delete_at_middle);
	mu_run_test(test_delete_at_end);
	mu_run_test(test_delete_at_after);
	mu_run_test(test_index_of_not_found);
	mu_run_test(test_index_of);

	return NULL;
}

RUN_TESTS(all_tests);