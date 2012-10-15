#include "sorting.h"

int check_sorted(vector_p vector, comparator_p comparator)
{
  for(size_t n = 1 ; n < vector->length; n++)
  {
    void *i = vector_get(vector, n - 1);
    void *j = vector_get(vector, n);
    
    if(comparator(i, j) > 0)
    {
      return 0;
    }
  }

  return 1;
}

void sort_selection(vector_p vector, comparator_p comparator)
{
  size_t n = vector->length;
  
  for(size_t i = 0 ; i < n ; ++i)
  {
    size_t min = i;

    for(size_t j = i + 1; j < n; j++)
    {
      if(comparator(vector->data[j], vector->data[min]) < 0)
      {
        min = j;
      }
    }

    vector_swap(vector, i, min);
  } 
}

void sort_insertion(vector_p vector, comparator_p comparator)
{
  size_t n = vector->length;

  for(size_t i = 1; i < n; i++)
  {
    for(size_t j = i ; j > 0 && comparator(vector->data[j], vector->data[j - 1]) < 0; j--)
    {
      vector_swap(vector, j, j - 1);
    }
  }
}

void sort_shell(vector_p vector, comparator_p comparator)
{
  size_t n = vector->length;
  size_t h = 1;
  
  while(h < n / 3)
  {
    h = (3 * h) + 1;
  }

  while(h >= 1)
  {
    for(size_t i = h ; i < n; i++)
    {
      for(size_t j = i; j >= h && comparator(vector->data[j], vector->data[j-h]) < 0; j -= h)
      {
        vector_swap(vector, j, j-h);
      }
    }

    h = h/3;
  }
}