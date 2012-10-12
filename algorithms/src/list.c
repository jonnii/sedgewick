#include "list.h"

list_p list_create()
{
	return calloc(1, sizeof(struct list));
}

void list_destroy(list_p list)
{
	free(list);
}

list_node *ListNode_create(void *item)
{
	list_node *node = calloc(1, sizeof(list_node));
	node->value = item;
	return node;
}

void list_add(list_p list, void *item)
{
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
	list->length++;
}

void *list_find_at(list_p list, int index)
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

void list_delete_at(list_p list, int index)
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

	list->length--;
}

int list_index_of(list_p list, void *value)
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

void list_clear(list_p list)
{
	for(list_node *curr = list->first ; curr != NULL; curr = curr->next)
	{
		free(curr->value);
		curr->value = NULL;
	}

	list->length = 0;
}

void list_clear_and_destroy(list_p list)
{
	list_node *node = list->first;
	while(node != NULL)
	{
		list_node *temp = node;
		node = node->next;

		free(temp->value);
		free(temp);
	}

	list->length = 0;
	list->first = NULL;
}