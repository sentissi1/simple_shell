#include "shell.h"

/**
 * _strcpy -A function that copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: destination
 */
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[x])
	{
		dest[x] = src[x];
		x++;
	}
	dest[x] = 0;
	return (dest);
}

/**
 * _str_dupl -A function that duplicates a string
 * @dstr: the string to duplicate
 *
 * Return: the duplicated string
 */
char *_str_dupl(const char *dstr)
{
	int len = 0;
	char *get;

	if (dstr == NULL)
		return (NULL);
	while (*dstr++)
		len++;
	get = malloc(sizeof(char) * (len + 1));
	if (!get)
		return (NULL);
	for (len++; len--;)
		get[len] = *--dstr;
	return (get);
}

/**
 *_put_input -A function that prints an input string
 *@str: the string that gonna be printed printed
 *
 * Return: None
 */
void _put_input(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_putchar(str[j]);
		j++;
	}
}

/**
 * _putchar -A function that writes the character c to stdout
 * @ch: The character to print
 *
 * Return: success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char ch)
{
	static int j;
	static char buff[WRITE_BUF_SIZE];

	if (ch == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buff, j);
		j = 0;
	}
	if (ch != BUF_FLUSH)
		buff[j++] = ch;
	return (1);
}

