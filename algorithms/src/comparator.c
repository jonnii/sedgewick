#include "comparator.h"

int compare_intp(void *i, void *j)
{
  return *((int*)i) - *((int*)j);
}