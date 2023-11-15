#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @data: struct @
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 * is_delimeter -A function that checks if character is a delimeter
 * @ch: the char to check
 * @deli: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delimeter(char ch, char *deli)
{
	while (*deli)
		if (*deli++ == ch)
			return (1);
	return (0);
}

/**
 *_is_alpha -A dunction checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi -A function that converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int j, sgn = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0;  str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			sgn *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sgn == -1)
		output = -result;
	else
		output = result;

	return (output);
}


