#ifndef _comparator_h
#define _comparator_h

typedef int (*comparator_p)(void *i, void *j);

int compare_intp(void *i, void *j);

#endif