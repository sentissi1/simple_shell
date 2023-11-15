#include "shell.h"

/**
 * **strtoi - splits a string into words.Repeat delimiters are ignored
 * @str: the input string
 * @deli: the delimeter string
 * Return: a pointer to an array of strings, or 0 on failure
 */

char **strtoi(char *str, char *deli)
{
	int i, j, k, l, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delimeter(str[i], deli) && (is_delimeter(str[i + 1], deli) || !str[i + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_delimeter(str[i], deli))
			i++;
		k = 0;
		while (!is_delimeter(str[i + k], deli) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **strtoi_2 - splits a string into words
 * @str: the input string
 * @deli: the delimeter
 * Return: a pointer to an array of strings, or 0 on failure
 */
char **strtoi_2(char *str, char deli)
{
	int i, j, k, l, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != deli && str[i + 1] == deli) ||
		    (str[i] != deli && !str[i + 1]) || str[i + 1] == deli)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < num_words; j++)
	{
		while (str[i] == deli && str[i] != deli)
			i++;
		k = 0;
		while (str[i + k] != deli && str[i + k] && str[i + k] != deli)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (l = 0; l < k; l++)
			s[j][l] = str[i++];
		s[j][l] = 0;
	}
	s[j] = NULL;
	return (s);
}

