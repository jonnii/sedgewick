#ifndef _comparator_h
#define _comparator_h

typedef int (*comparator_p)(const void *i, const void *j);

int compare_intp(const void *i, const void *j);

#endif