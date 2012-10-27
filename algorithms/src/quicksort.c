#include "quicksort.h"
#include "sorting.h"

#define CUT_OFF_TO_INSERTION_SORT 10

void quicksort_range(vector_p vector, int lo, int hi, comparator_p comparator)
{
  if(hi - lo < CUT_OFF_TO_INSERTION_SORT)
  {
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
  sort_insertion(vector, comparator);
}

void quicksort3_range(vector_p vector, int lo, int hi, comparator_p comparator)
{
  if(hi - lo < CUT_OFF_TO_INSERTION_SORT)
  {
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
  sort_insertion(vector, comparator);
}

void quicksortp_range(vector_p vector, int lo, int hi, comparator_p comparator)
{
  if(hi - lo < CUT_OFF_TO_INSERTION_SORT)
  {
    return; 
  }

  int mid = lo + ((hi - lo) / 2);

  // use a median of three sorting, this will put
  // lo, mid and hi in the correct order
  if(comparator(vector_get(vector, mid), vector_get(vector, lo)) < 0)
  {
    vector_swap(vector, mid, lo);
  }

  if(comparator(vector_get(vector, hi), vector_get(vector, mid)) < 0)
  {
    vector_swap(vector, mid, hi);
  
    if(comparator(vector_get(vector, mid), vector_get(vector, lo)) < 0)
    {
      vector_swap(vector, mid, lo);
    }
  }

  int i = lo;
  int j = hi - 1;
  void *v = vector_get(vector, mid);

  do
  {
    // scan left
    while(comparator(vector_get(vector, i), v) < 0)
    {
      i++;
    }

    // scan right
    while(comparator(v, vector_get(vector, j)) < 0)
    {
      j--;
    }

    if(i < j)
    {    
      vector_swap(vector, i, j);

      if (mid == i)
      {
        mid = j;
      }
      else if (mid == j)
      {
        mid = i;
      }

      i++;
      j--;
    }
    else if(i == j){             
      i++;
      j--;
      break;
    }

  } while(i <= j);

  quicksort_range(vector, lo, j, comparator);
  quicksort_range(vector, i, hi, comparator);
}

void quicksortp(vector_p vector, comparator_p comparator)
{
  quicksortp_range(vector, 0, vector->length - 1, comparator);
  sort_insertion(vector, comparator);
}