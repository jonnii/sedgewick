#ifndef _linked_list_h
#define _linked_list_h

#include <stdlib.h>

typedef struct list_node {
	struct list_node *next;
	void *value;
} list_node;

struct list {
	list_node *first;
};

typedef struct list* list_p;

list_p list_create();

void list_destroy(list_p list);

void list_add(list_p list, void *item);

void list_clear(list_p list);

void list_clear_and_destroy(list_p list);

void *list_find_at(list_p list, int index);

int list_count(list_p list);

void list_delete_at(list_p list, int index);

int list_index_of(list_p list, void *value);

//bool List_delete_after(void *value);

//bool List_insert_at(int i, void *value);

//bool List_insert_after(void *value, void *value);

//bool List_remove_matching(LinkedList *list, List_value_compare comparer);

//void List_reverse(List* list);

#endif