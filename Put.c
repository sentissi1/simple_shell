#include "shell.h"

/**
 *_Put -A function that prints an input string
 * @Str: A string to be printed
 *
 * Return: None
 */
void _Put(char *Str)
{
	int p = 0;

	if (!Str)
		return;
	while (Str[p] != '\0')
	{
		_Putchar(Str[p]);
		p++;
	}
}

/**
 * _Putchar -A function that writes the character s to standaet out
 * @s: A character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _Putchar(char s)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buffer, j);
		j = 0;
	}
	if (s != BUF_FLUSH)
		buffer[j++] = s;
	return (1);
}

/**
 * _PutDf -A function that writes the character c to given Df
 * @s: A character to print
 * @Df : The Description file to write into
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _PutDf(char s, int Df)
{
	static int n;
	static char buffer[WRITE_BUF_SIZE];

	if (s == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(Df, buffer, n);
		n = 0;
	}
	if (s != BUF_FLUSH)
		buffer[n++] = s;
	return (1);
}

/**
 *_Put_str_input - prints an input string
 * @Str: a string to be printed
 * @D: The Description to write into
 *
 * Return: the number of chars put
 */
int _Put_str_input(char *Str, int D)
{
	int n = 0;

	if (!Str)
		return (0);
	while (*Str)
	{
		n += _PutDf(*Str++, D);
	}
	return (n);
}

