#include "sorting.h"
#include "math.h"
#include <string.h>
#include <stdio.h>

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

void sort_sub_insertion(vector_p vector, comparator_p comparator, size_t lo, size_t hi)
{
  size_t n = hi - lo;

  for(size_t i = 1; i < n; i++)
  {
    for(size_t j = i ; j > 0 && comparator(
        vector->data[lo + j], 
        vector->data[lo + j - 1]) < 0; j--)
    {
      vector_swap(vector, lo + j, lo + j - 1);
    }
  }
}

void sort_insertion(vector_p vector, comparator_p comparator)
{
  size_t n = vector->length;
  sort_sub_insertion(vector, comparator, 0, n);
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

void merge(void **temp, vector_p vector, comparator_p comparator, int lo, int mid, int hi)
{
  int i = lo;
  int j = mid + 1;

  for(int k = lo; k <= hi; k++)
  {
    temp[k] = vector->data[k];
  }
  
  for(int k = lo; k <= hi; k++)
  {
    if(i > mid)
    {
      vector->data[k] = temp[j++];
    }
    else if(j > hi)
    {
      vector->data[k] = temp[i++];
    }
    else if(comparator(temp[j], temp[i]) < 0)
    {
      vector->data[k] = temp[j++];
    }
    else
    {
      vector->data[k] = temp[i++];
    }
  }
}

void sort_merge_range(void **temp, vector_p vector, comparator_p comparator, int lo, int hi)
{
  if(hi <= lo)
  {
    return;
  }

  int range = hi - lo + 1;
  if(range <= 15)
  {
    sort_sub_insertion(vector, comparator, lo, hi + 1);
    return;
  }

  int mid = lo + (hi - lo) / 2;
    
  sort_merge_range(temp, vector, comparator, lo, mid);
  sort_merge_range(temp, vector, comparator, mid + 1, hi);
  
  if(comparator(vector_get(vector, mid), vector_get(vector, mid + 1)) < 0)
  {
    return;
  }

  merge(temp, vector, comparator, lo, mid, hi);
}

void sort_merge(vector_p vector, comparator_p comparator)
{
  void** copy = calloc(vector->length, sizeof(void*));
  sort_merge_range(copy, vector, comparator, 0, vector->length - 1);
  free(copy);
}

void sort_merge_bu(vector_p vector, comparator_p comparator)
{
  void** temp = calloc(vector->length, sizeof(void*));
  int n = vector->length;
  
  for(int sz = 1; sz < n; sz = sz + sz)
  {
    for(int lo = 0 ; lo < n - sz; lo += sz + sz)
    {
      int hi = min(lo + sz + sz - 1, n - 1); 
      merge(temp, vector, comparator, lo, lo + sz - 1, hi);
    }
  }  
  
  free(temp);
}