#include "shell.h"

/**
 * _strlen -A function that returns the length of a string
 * @s: sting
 *
 * Return: length
 */
int _strlen(char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (*s++)
		len++;
	return (len);
}

/**
 * _strcmp -A function that compare 2 strings
 * @s1: string 1
 * @s2: string 2
 *
 * Return: s1 and s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * begin_func -A function that checks if substr begin with str
 * @str: string to look for
 * @substr: the substring to get
 *
 * Return: @ of next char of str or 0
 */
char *begin_func(const char *str, const char *substr)
{
	while (*substr)
		if (*substr++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strcat -a function that concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: destination
 */

char *_strcat(char *dest, char *src)
{
	int i;
	int k;

	i = 0;
	while (dest[i] != '\0')
	{
		i = i + 1;
	}
	k = 0;
	while (src[k] != '\0')
	{
		dest[i] = src[k];
		i++;
		k++;
	}
	dest[i] = '\0';
	return (dest);
}

