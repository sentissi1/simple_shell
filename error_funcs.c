#include "shell.h"

/**
 * _convert_func -A function that converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _convert_func(char *str)
{
	int j = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;  /* TODO: why does this make main return 255? */
	for (j = 0;  str[j] != '\0'; j++)
	{
		if (str[j] >= '0' && str[j] <= '9')
		{
			result *= 10;
			result += (str[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * error_print_msg - prints an error message
 * @data: the parameter and return data struct
 * @errs: string that could contain specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void error_print_msg(data_t *data, char *errs)
{
	_Put(data->fname);
	_Put(": ");
	prints_dc(data->line_count, STDERR_FILENO);
	_Put(": ");
	_Put(data->argv[0]);
	_Put(": ");
	_Put(errs);
}

/**
 * prints_dc - A function prints a decimal (integer)
 * @input:An input
 * @DF: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int prints_dc(int input, int DF)
{
	int (*__putchar)(char) = _putchar;
	int j, counter = 0;
	unsigned int _abs_, current;

	if (DF == STDERR_FILENO)
		__putchar = _Putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counter++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			counter++;
		}
		current %= j;
	}
	__putchar('0' + current);
	counter++;

	return (counter);
}

/**
 * convert_num - converter function, a clone of itoa
 * @Num: number
 * @Base: base
 * @Flag: argument flags
 *
 * Return: string
 */
char *convert_num(long int Num, int Base, int Flag)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long N = Num;

	if (!(Flag & CONVERT_UNSIGNED) && Num < 0)
	{
		N = -Num;
		sign = '-';

	}
	array = Flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[N % Base];
		N /= Base;
	} while (N != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * delete_comments - A function That replaces first instance of '#' with '\0'
 * @Buff: address of the string to modify
 *
 * Return: Always 0;
 */
void delete_comments(char *Buff)
{
	int j;

	for (j = 0; Buff[j] != '\0'; j++)
		if (Buff[j] == '#' && (!j || Buff[j - 1] == ' '))
		{
			Buff[j] = '\0';
			break;
		}
}

