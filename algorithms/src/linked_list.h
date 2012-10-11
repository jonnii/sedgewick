#ifndef _linked_list_h
#define _linked_list_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
	struct ListNode *next;
	void *value;
} ListNode;

typedef struct List {
	ListNode *first;
} List;

List *List_create();

void List_destroy(List *list);

void List_add(List *list, void *item);

void List_clear(List *list);

void List_clear_and_destroy(List *list);

void *List_find_index(List *list, int index);

#endif