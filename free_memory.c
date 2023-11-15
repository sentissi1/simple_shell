#include "shell.h"

/**
 * Bfree -A function that frees a pointer and empty the @
 * @pr: @ of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int Bfree(void **pr)
{
	if (pr && *pr)
	{
		free(*pr);
		*pr = NULL;
		return (1);
	}
	return (0);
}

