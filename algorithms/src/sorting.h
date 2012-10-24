#ifndef _sorting_h
#define _sorting_h

#include "vector.h"
#include "comparator.h"

typedef void (*sorter_p)(vector_p vector, comparator_p comparator);

int check_sorted(vector_p vector, comparator_p comparator);

void sort_selection(vector_p vector, comparator_p comparator);

void sort_insertion(vector_p vector, comparator_p comparator);

void sort_sub_insertion(vector_p vector, comparator_p comparator, size_t lo, size_t hi);

void sort_shell(vector_p vector, comparator_p comparator);

void sort_merge(vector_p vector, comparator_p comparator);

void sort_merge_bu(vector_p vector, comparator_p comparator);

#endif