#include "linked_list.h"
#include "dbg.h"

list_p LinkedList_create()
{
	list_p list = calloc(1, sizeof(struct list));
	check_mem(list);
	return list; 
error:
	log_err("Could not allocate memory for list");
	return NULL;
}

void LinkedList_destroy(list_p list)
{
	free(list);
}

list_node *ListNode_create(void *item){
	list_node *node = calloc(1, sizeof(list_node));
	check_mem(node);
	node->value = item;
	return node;
error:
	log_err("Could not allocate memory for list node");
	return NULL;
}

void LinkedList_add(list_p list, void *item)
{
	check_debug(list != NULL, "Cannot add an item to a NULL list");
	check_debug(item != NULL, "Cannot add a NULL item");

	list_node *node = ListNode_create(item);
	if(list->first == NULL)
	{
		list->first = node;
	}
	else
	{
		list_node *curr = list->first;
		while(curr->next != NULL)
		{
			curr = curr->next;
		}
		curr->next = node;
	}
error:
	log_err("Could not add an item to the list");
}

void *LinkedList_find_at(list_p list, int index)
{
	if(list->first == NULL)
	{
		return NULL;
	}

	list_node *node = list->first;
	
	for(int i = 0 ; i < index ; ++i){
		if(node->next == NULL)
		{
			return NULL;
		}

		node = node->next;
	}

	return node->value;
}

int LinkedList_count(list_p list)
{
	list_node *node = list->first;
	int count = 0;
	
	while(node != NULL)
	{
		node = node->next;
		++count;
	}

	return count;
}

void LinkedList_delete_at(list_p list, int index)
{
	if(list->first == NULL)
	{
		return;
	}

	list_node *curr = list->first;

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
		
		list_node *temp = curr->next;

		curr->next = curr->next->next;
		curr = curr->next;

		free(temp->value);
		free(temp);
	}
}

int LinkedList_index_of(list_p list, void *value)
{
	list_node *curr = list->first;
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

void LinkedList_clear(list_p list)
{
	for(list_node *curr = list->first ; curr != NULL; curr = curr->next)
	{
		free(curr->value);
		curr->value = NULL;
	}
}

void LinkedList_clear_and_destroy(list_p list)
{
	list_node *node = list->first;
	while(node != NULL)
	{
		list_node *temp = node;
		node = node->next;

		free(temp->value);
		free(temp);
	}

	list->first = NULL;
}