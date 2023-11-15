#include "shell.h"

/**
 * _History_fun -a function that displays the history list
 * @data:a structure that could contain potential arguments.
 *
 *  Return: Always 0
 */
int _History_fun(data_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 * alias_UNSET -a function that sets alias to string
 * @data: parameter struct
 * @Str: A string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_UNSET(data_t *data, char *Str)
{
	char *i, j;
	int det;

	i = _strchr(Str, '=');
	if (!i)
		return (1);
	j = *i;
	*i = 0;
	det = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, Str, -1)));
	*i = j;
	return (det);
}

/**
 * alias_SET -a function that sets alias to a string
 * @data: A parameter struct
 * @Str: A string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_SET(data_t *data, char *Str)
{
	char *i;

	i = _strchr(Str, '=');
	if (!i)
		return (1);
	if (!*++i)
		return (alias_UNSET(data, Str));

	alias_UNSET(data, Str);
	return (add_node_end(&(data->alias), Str, 0) == NULL);
}

/**
 * alias_to_print -A functiom that prints an alias string
 * @nodd: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int alias_to_print(list_t *nodd)
{
	char *i = NULL, *e = NULL;

	if (nodd)
	{
		i = _strchr(nodd->sr, '=');
		for (e = nodd->sr; e <= i; e++)
			_putchar(*e);
		_putchar('\'');
		_put_input(i + 1);
		_put_input("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias_func -A function that mimics the alias builtin
 * @data:a structure that could contain potential arguments
 *
 *  Return: Always 0
 */
int _alias_func(data_t *data)
{
	int i = 0;
	char *j = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			alias_to_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		j = _strchr(data->argv[i], '=');
		if (j)
			alias_SET(data, data->argv[i]);
		else
			alias_to_print(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}

