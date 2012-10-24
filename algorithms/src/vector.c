#include "vector.h"
#include <stdlib.h>
#include <string.h>

#include <stdio.h>

#define DEFAULT_INITIAL_CAPACITY 10

vector_p vector_create_with_capacity(size_t element_size, int capacity)
{
  vector_p vector = calloc(1, sizeof(struct vector));

  vector->capacity = capacity;
  vector->data = calloc(capacity, sizeof(void*));
  vector->create_element = NULL;
  vector->free_element = NULL;
  vector->element_size = element_size;

  return vector;
}

vector_p vector_create(size_t element_size)
{
  return vector_create_with_capacity(element_size, DEFAULT_INITIAL_CAPACITY);
}

void vector_free(vector_p vector)
{
  if(vector->free_element != NULL)
  {
    for(size_t i = 0 ; i < vector->length ; ++i)
    {
      vector->free_element(vector->data[i]);
    }
  }

  free(vector->data);
  free(vector);
}

vector_p vector_copy_shallow(vector_p original)
{
  vector_p copy = vector_create_with_capacity(
    original->element_size, 
    original->capacity);

  copy->create_element = original->create_element;
  copy->free_element = original->free_element;
  copy->length = original->length;
  memcpy(copy->data, original->data, original->capacity * sizeof(void*));

  return copy;
}

void *copy_element(vector_p vector, void *data)
{
  void *target = malloc(vector->element_size);
  memcpy(target, data, vector->element_size);
  return target;
}

void vector_copy_elements(vector_p vector)
{
  vector->create_element = copy_element;
  vector->free_element = free; 
}

void vector_expand(vector_p vector)
{
  vector->capacity *= 2;
  vector->data = (void**) realloc (vector->data, sizeof(void*) * vector->capacity);
}

void *vector_get_element_data(vector_p vector, void *data)
{
  void *element = data;

  if(vector->create_element != NULL) {
    element = vector->create_element(vector, element);
  }

  return element;
}

void vector_maybe_expand(vector_p vector)
{
  if(vector->length == vector->capacity)
  {
    vector_expand(vector);
  }
}

void vector_maybe_contract(vector_p vector)
{
  if(vector->length -1 < vector->capacity / 4)
  {
    vector->capacity /= 4;
    vector->data = (void**) realloc (vector->data, sizeof(void*) * vector->capacity);
  }
}

size_t vector_add(vector_p vector, void *data)
{
  vector_maybe_expand(vector);

  int offset = vector->length;
  
  vector->data[offset] = vector_get_element_data(vector, data);
  vector->length++;

  return offset;
}

void *vector_get(vector_p vector, size_t index)
{
  if(index > vector->length)
  {
    return NULL;
  }

  return vector->data[index];
}

int vector_set(vector_p vector, size_t index, void *data)
{
  if(index > vector->length)
  {
    return 0;
  }

  if(vector->free_element != NULL && vector->data[index] != NULL)
  {
    vector->free_element(vector->data[index]);
  }

  vector->data[index] = vector_get_element_data(vector, data);
  
  return 1;
}

int vector_swap(vector_p vector, int i, int j)
{
  if(i == j)
  {
    return 1;
  }

  void *temp = vector->data[j];
  vector->data[j] = vector->data[i];
  vector->data[i] = temp;
  
  return 1;
}

void vector_remove(vector_p vector, size_t index)
{
  if(index > vector->length)
  {
    return;
  }

  if(vector->free_element)
  {
    vector->free_element(vector->data[index]);
  }

  for(size_t i = index; i < vector->length ; ++i)
  {
    vector->data[i] = vector->data[i+1];
  }

  --vector->length;

  vector_maybe_contract(vector);
}

int vector_insert(vector_p vector, size_t index, void *data)
{
  vector_maybe_expand(vector);

  for(size_t i = vector->length; i > index; i--)
  {
    vector->data[i] = vector->data[i-1];
  }

  vector->length++;
  vector->data[index] = vector_get_element_data(vector, data);

  return 1;
}

void *vector_next(iterator_p iterator)
{
  vector_iterator_p context = (vector_iterator_p)iterator->context;

  if(iterator->current == NULL)
  {
    iterator->current = context->vector->data[0];
    return iterator->current;
  }

  if(context->current_index == context->vector->length)
  {
    free(iterator->context);
    free(iterator);
    return NULL;
  }

  context->current_index++;
  iterator->current = context->vector->data[context->current_index];

  return iterator->current;
}

iterator_p vector_iterator(vector_p vector)
{
  vector_iterator_p context = (vector_iterator_p)malloc(sizeof(vector_iterator_p));  
  context->current_index = 0;
  context->vector = vector;

  iterator_p iterator = (iterator_p)malloc(sizeof(iterator_p));
  iterator->next = vector_next;  
  iterator->context = context; 
  iterator->current = NULL;

  return iterator;
}