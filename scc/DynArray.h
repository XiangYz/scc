#ifndef _DYN_ARRAY_
#define _DYN_ARRAY_


#include <stdio.h>
#include <stdlib.h>

typedef struct DynArray
{
	int count;      //void*的个数
	int capacity;   //总字节数
	void** data;
}DynArray;



void dynarray_init(DynArray* parr, int initsize);
void dynarray_free(DynArray* parr);
void dynarray_realloc(DynArray* parr, int new_size);
void dynarray_add(DynArray* parr, void* data);
int dynarray_search(DynArray* parr, int key);



#endif
