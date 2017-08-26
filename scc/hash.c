#include "hash.h"

int elf_hash(char* key)
{
	int h = 0, g;
	while (*key)
	{
		h = (h << 4) + *key++;
		g = h & 0xF0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}

	return h % MAXKEY;
}
