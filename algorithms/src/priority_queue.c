#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

priority_queue_p priority_queue_create(size_t element_size, comparator_p comparator)
{
	priority_queue_p queue = calloc(1, sizeof(priority_queue_p));
	
  queue->vector = vector_create(element_size);
  queue->comparator = comparator;

	return queue;
}

void priority_queue_free(priority_queue_p queue)
{
	vector_free(queue->vector);
	free(queue);
}

void swim(priority_queue_p queue, size_t index)
{
  vector_p vector = queue->vector;
  comparator_p comparator = queue->comparator;
  
  while (index > 1 && 
    comparator(vector_get(vector, index/2), vector_get(vector, index)) < 0)
  {
    vector_swap(vector, index, index/2);
    index = index/2;
  }
}

void priority_queue_insert(priority_queue_p queue, void *value)
{
	int index = vector_add(queue->vector, value);
	swim(queue, index);
}