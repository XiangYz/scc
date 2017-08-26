#include "DynString.h"
#include "error.h"

void dynstring_init(DynString* pstr, int initsize)
{
	if (pstr != NULL)
	{
		pstr->data = (char*)malloc(sizeof(char) * initsize);
		pstr->count = 0;
		pstr->capacity = initsize;
	}
}

void dynstring_free(DynString* pstr)
{
	if (pstr != NULL)
	{
		if (pstr->data)
			free(pstr->data);
		pstr->data = NULL;
		pstr->count = 0;
		pstr->capacity = 0;
	}
}


void dynstring_reset(DynString* pstr)
{
	dynstring_free(pstr);
	dynstring_init(pstr, 8);
}

void dynstring_realloc(DynString* pstr, int new_size)
{
	int capacity;
	char* data;

	capacity = pstr->capacity;
	while (capacity < new_size)
	{
		capacity *= 2;
	}
	data = (char*)realloc(pstr->data, capacity);
	if (!data)
		error("ÄÚ´æ·ÖÅäÊ§°Ü");
	pstr->capacity = capacity;
	pstr->data = data;

}

void dynstring_chcat(DynString* pstr, int ch)
{
	int count;
	count = pstr->count + 1;
	if (count > pstr->capacity)
	{
		dynstring_realloc(pstr, count);
	}
	((char*)pstr->data)[count - 1] = ch;
	pstr->count = count;
}
