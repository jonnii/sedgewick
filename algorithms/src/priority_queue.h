#ifndef _priority_queue_h
#define _priority_queue_h

#include "comparator.h"
#include "vector.h"

struct priority_queue
{
	vector_p vector;
	comparator_p comparator;
};

typedef struct priority_queue * priority_queue_p;

priority_queue_p priority_queue_create(size_t element_size, comparator_p comparator);

void priority_queue_free(priority_queue_p queue);

void priority_queue_insert(priority_queue_p queue, void *value);

#endif