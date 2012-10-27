#include "comparator.h"

int compare_intp(const void *i, const void *j)
{
  return *((int*)i) - *((int*)j);
}