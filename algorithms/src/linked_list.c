#include "linked_list.h"
#include "dbg.h"

List *List_create()
{
	List *list = calloc(1, sizeof(List));
	check_mem(list);
	return list; 
error:
	log_err("Could not allocate memory for list");
	return NULL;
}

void List_destroy(List *list)
{
	free(list);
}

ListNode *ListNode_create(void *item){
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);
	node->value = item;
	return node;
error:
	log_err("Could not allocate memory for list node");
	return NULL;
}

void List_add(List *list, void *item)
{
	check_debug(list != NULL, "Cannot add an item to a NULL list");
	check_debug(item != NULL, "Cannot add a NULL item");

	ListNode *node = ListNode_create(item);
	if(list->first == NULL)
	{
		list->first = node;
	}
	else
	{
		ListNode *curr = list->first;
		while(curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = node;
	}
error:
	log_err("Could not add an item to the list");
}

void List_clear(List *list)
{
	for(ListNode *curr = list->first ; curr != NULL; curr = curr->next)
	{
		free(curr->value);
		curr->value = NULL;
	}
}

void List_clear_and_destroy(List *list)
{
	ListNode *node = list->first;
	while(node != NULL)
	{
		ListNode *temp = node;
		node = node->next;

		free(temp->value);
		free(temp);
	}

	list->first = NULL;
}