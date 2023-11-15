#include "shell.h"

/**
 * _Get_env_func -A function that prints the current environment
 * @data: A structure could contain potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _Get_env_func(data_t *data)
{
	print_list_str(data->env);
	return (0);
}

/**
 * _Env_func -a function that gets the value of an environment Var
 * @data: a structure could contain potential args. Used to maintain
 * @Name: environment variable name
 *
 * Return: the value
 */
char *_Env_func(data_t *data, const char *Name)
{
	list_t *node = data->env;
	char *i;

	while (node)
	{
		i = begin_func(node->sr, Name);
		if (i && *i)
			return (i);
		node = node->next;
	}
	return (NULL);
}

/**
 * _New_env_var -A function that initialize a new environment variable,
 *
 * @data: a structure could contain potential args
 *
 *  Return: Always 0
 */
int _New_env_var(data_t *data)
{
	if (data->argc != 3)
	{
		_Put("Invvalid Number of Args\n");
		return (1);
	}
	if (_setenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _UNSET_env_func -A function that remove an env var.
 * @data:a structure could contain potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _UNSET_env_func(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_Put("More Arguments.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_unsetenv(data, data->argv[i]);

	return (0);
}

/**
 * _Env_List - populates env linked list
 * @data: A structure could contain potential args. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _Env_List(data_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	data->env = node;
	return (0);
}

