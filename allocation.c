#include "shell.h"

/**
 **_memset_func -A function that fills memory with a constant byte
 *@p: the pointer to the memory area
 *@b: the byte to fill *s with
 *@a: the amount of bytes to be filled
 *Return: a pointer to the memory area p
 */
char *_memset_func(char *p, char b, unsigned int a)
{
	unsigned int x;

	for (x = 0; x < a; x++)
		p[x] = b;
	return (p);
}

/**
 * free_func -A function that frees a string of strings
 * @ss: string of strings
 */
void free_func(char **ss)
{
	char **a = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(a);
}

/**
 * _realloc_func -A function that reallocates a block of memory
 * @pointr: pointer to previous mallocated block of memory
 * @old_sz: size of previous block
 * @nw_sz: size of new block
 *
 * Return: pointer to da old block of memory.
 */
void *_realloc_func(void *pointr, unsigned int old_sz, unsigned int nw_sz)
{
	char *s;

	if (!pointr)
		return (malloc(nw_sz));
	if (!nw_sz)
		return (free(pointr), NULL);
	if (nw_sz == old_sz)
		return (pointr);

	s = malloc(nw_sz);
	if (!s)
		return (NULL);

	old_sz = old_sz < nw_sz ? old_sz : nw_sz;
	while (old_sz--)
		s[old_sz] = ((char *)pointr)[old_sz];
	free(pointr);
	return (s);
}

