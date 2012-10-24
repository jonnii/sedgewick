#include "quicksort.h"

#define CUT_OFF_TO_INSERTION_SORT 10

void quicksort_range(vector_p vector, int lo, int hi, comparator_p comparator)
{
  if(hi - lo < CUT_OFF_TO_INSERTION_SORT)
  {
    sort_sub_insertion(vector, comparator, lo, hi + 1);
    return; 
  }

  // parition
  int i = lo;
  int j = hi + 1;
  void *v = vector_get(vector, lo);

  while(1)
  {
    // scan left
    while(comparator(vector_get(vector, ++i), v) < 0)
    {
      if(i == hi)
      {
        break;
      }
    }

    // scan right
    while(comparator(v, vector_get(vector, --j)) < 0)
    {
    }

    if(i >= j)
    {
      break;
    }

    // exchange
    vector_swap(vector, i, j);
  }

  // final exchange to put pivot in correct place
  vector_swap(vector, lo, j);

  quicksort_range(vector, lo, j - 1, comparator);
  quicksort_range(vector, j + 1, hi, comparator);
}

void quicksort(vector_p vector, comparator_p comparator)
{
  quicksort_range(vector, 0, vector->length - 1, comparator);
}

void quicksort3_range(vector_p vector, int lo, int hi, comparator_p comparator)
{
  if(hi - lo < CUT_OFF_TO_INSERTION_SORT)
  {
    sort_sub_insertion(vector, comparator, lo, hi + 1);
    return; 
  }
  
  int lt = lo;
  int gt = hi;
  
  void *v = vector_get(vector, lo);
  
  int i = lo;
  while (i <= gt)
  {
    void *a = vector_get(vector, i);
    int cmp = comparator(a, v);
    
    if (cmp < 0)
    {
      vector_swap(vector, lt++, i++);
    }
    else if (cmp > 0)
    {
      vector_swap(vector, i, gt--);
    }
    else
    {
      i++;
    }
  }

  quicksort3_range(vector, lo, lt-1, comparator);
  quicksort3_range(vector, gt+1, hi, comparator);
}

void quicksort3(vector_p vector, comparator_p comparator)
{
  quicksort3_range(vector, 0, vector->length - 1, comparator);
}