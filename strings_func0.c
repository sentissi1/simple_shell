#include "shell.h"

/**
 **_strncpy - A function that copies a string
 *@Dest: destination
 *@Src: source
 *@c: the amount of characters to be copied
 *Return: string
 */
char *_strncpy(char *Dest, char *Src, int m )
{
	int x, y;
	char *c = Dest;

	x = 0;
	while (Src[x] != '\0' && x < m - 1)
	{
		Dest[x] = Src[x];
		x++;
	}
	if (x < m)
	{
		y = x;
		while (y < m)
		{
			Dest[y] = '\0';
			y++;
		}
	}
	return (c);
}

/**
 **_strncat -a function that concatenates two strings
 *@Dest: first string
 *@Src: second string
 *@c: the amount of bytes to be maximally used
 *Return: string
 */
char *_strncat(char *Dest, char *Src, int c)
{
	int x, y;
	char *str = Dest;

	x = 0;
	y = 0;
	while (Dest[x] != '\0')
		x++;
	while (Src[y] != '\0' && y < c)
	{
		Dest[x] = Src[y];
		x++;
		y++;
	}
	if (y < c)
		Dest[x] = '\0';
	return (str);
}

/**
 **_strchr -a function that locates a character in a string
 *@str: the string to be parsed
 *@ch: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

