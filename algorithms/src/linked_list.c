#include "linked_list.h"

List *List_create()
{
	return calloc(1, sizeof(List));
}

void List_destroy(struct List *list)
{
	free(list);
} 