#ifndef _iterator_h
#define _iterator_h

#include <stdlib.h>

typedef struct iterator
{
  void *current;
  void *context;
  void *(*next)(struct iterator *iterator);
} iterator;

typedef iterator * iterator_p;

void *iterator_next(iterator_p iterator);

#endif