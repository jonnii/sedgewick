#ifndef _vector_h
#define _vector_h

#include <stdlib.h>

struct vector{
	size_t length;
	size_t capacity;
};

typedef struct vector* vector_p;

vector_p vector_create();

vector_p vector_create_with_capacity(int capacity);

#endif