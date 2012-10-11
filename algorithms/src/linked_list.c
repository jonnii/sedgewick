#include "linked_list.h"
#include "dbg.h"

LinkedList *LinkedList_create()
{
	LinkedList *list = calloc(1, sizeof(LinkedList));
	check_mem(list);
	return list; 
error:
	log_err("Could not allocate memory for list");
	return NULL;
}

void LinkedList_destroy(LinkedList *list)
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

void LinkedList_add(LinkedList *list, void *item)
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

void *LinkedList_find_at(LinkedList *list, int index)
{
	if(list->first == NULL)
	{
		return NULL;
	}

	ListNode *node = list->first;
	
	for(int i = 0 ; i < index ; ++i){
		if(node->next == NULL)
		{
			return NULL;
		}

		node = node->next;
	}

	return node->value;
}

int LinkedList_count(LinkedList *list)
{
	ListNode *node = list->first;
	int count = 0;
	
	while(node != NULL)
	{
		node = node->next;
		++count;
	}

	return count;
}

void LinkedList_delete_at(LinkedList *list, int index)
{
	if(list->first == NULL)
	{
		return;
	}

	ListNode *curr = list->first;

	if(index == 0)
	{		
		list->first = curr->next;
		free(curr->value);
		free(curr);
	}
	else
	{
		for(int i = 0 ; i < index - 1; ++i)
		{
			curr = curr->next;

			if(curr == NULL)
			{
				return;
			}
		}
		
		ListNode *temp = curr->next;

		curr->next = curr->next->next;
		curr = curr->next;

		free(temp->value);
		free(temp);
	}
}

int LinkedList_index_of(LinkedList *list, void *value)
{
	ListNode *curr = list->first;
	int index = 0;
	while(curr != NULL)
	{
		if(curr->value == value)
		{
			return index;
		}

		curr = curr->next;
		++index;
	}

	return -1;
}

void LinkedList_clear(LinkedList *list)
{
	for(ListNode *curr = list->first ; curr != NULL; curr = curr->next)
	{
		free(curr->value);
		curr->value = NULL;
	}
}

void LinkedList_clear_and_destroy(LinkedList *list)
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