#include "iterator.h"

void *iterator_next(iterator_p iterator)
{
  return iterator->next(iterator);
}