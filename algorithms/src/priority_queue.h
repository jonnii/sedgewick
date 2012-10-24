#ifndef _priority_queue_h
#define _priority_queue_h

#include "vector.h"

struct priority_queue
{
	vector_p vector;
};

typedef struct priority_queue * priority_queue_p;

priority_queue_p priority_queue_create(size_t element_size);

void priority_queue_free(priority_queue_p queue);

#endif