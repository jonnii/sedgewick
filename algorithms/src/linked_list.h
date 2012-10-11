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

LinkedList *LinkedList_create();

void LinkedList_destroy(LinkedList *list);

void LinkedList_add(LinkedList *list, void *item);

void LinkedList_clear(LinkedList *list);

void LinkedList_clear_and_destroy(LinkedList *list);

void *LinkedList_find_at(LinkedList *list, int index);

int LinkedList_count(LinkedList *list);

void LinkedList_delete_at(LinkedList *list, int index);

//bool List_exists(void *value);

//bool List_delete_after(void *value);

//bool List_insert_at(int i, void *value);

//bool List_insert_after(void *value, void *value);

//bool List_remove_matching(LinkedList *list, List_value_compare comparer);

//void List_reverse(List* list);

#endif