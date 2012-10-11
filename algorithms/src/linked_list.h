#ifndef _linked_list_h
#define _linked_list_h

#include <stdlib.h>

struct ListNode;

typedef struct ListNode {
	struct ListNode *next;
	void *value;
} ListNode;

typedef struct LinkedList {
	ListNode *first;
} LinkedList;

LinkedList *List_create();

void List_destroy(LinkedList *list);

void List_add(LinkedList *list, void *item);

void List_clear(LinkedList *list);

void List_clear_and_destroy(LinkedList *list);

void *List_find_at(LinkedList *list, int index);

int List_count(LinkedList *list);

//void List_delete_at(LinkedList *list, int i);

//bool List_exists(void *value);

//bool List_delete_after(void *value);

//bool List_insert_at(int i, void *value);

//bool List_insert_after(void *value, void *value);

//bool List_remove_matching(LinkedList *list, List_value_compare comparer);

//void List_reverse(List* list);

#endif