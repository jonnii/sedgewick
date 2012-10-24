#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

priority_queue_p priority_queue_create(size_t element_size)
{
	priority_queue_p queue = calloc(1, sizeof(priority_queue_p));
	queue->vector = vector_create(element_size);

	return queue;
}

void priority_queue_free(priority_queue_p queue)
{
	vector_free(queue->vector);
	free(queue);
}

