#ifndef _sorting_h
#define _sorting_h

#include "vector.h"

typedef int (*comparator_p)(void *i, void *j);

int check_sorted(vector_p vector, comparator_p comparator);

void sort_selection(vector_p vector, comparator_p comparator);

void sort_insertion(vector_p vector, comparator_p comparator);

void sort_shell(vector_p vector, comparator_p comparator);

#endif