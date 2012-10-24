#ifndef _sorting_h
#define _sorting_h

#include "vector.h"

typedef int (*comparator_p)(void *i, void *j);

typedef void (*sorter_p)(vector_p vector, comparator_p comparator);

int check_sorted(vector_p vector, comparator_p comparator);

void sort_selection(vector_p vector, comparator_p comparator);

void sort_insertion(vector_p vector, comparator_p comparator);

void sort_shell(vector_p vector, comparator_p comparator);

void sort_merge(vector_p vector, comparator_p comparator);

void sort_merge_bu(vector_p vector, comparator_p comparator);

void sort_quicksort(vector_p vector, comparator_p comparator);

void sort_quicksort3(vector_p vector, comparator_p comparator);

int compare_intp(void *i, void *j);

#endif