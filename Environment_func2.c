#include "shell.h"

/**
 * Get_env -a function that returns the string array copy of our environment
 * @data: A structure could contain potential arguments
 *
 * Return: Always 0
 */
char **Get_env(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_str(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * _unsetenv -A function that remove an env var
 * @data: A structure could contain potential arguments
 *
 *  Return: 1 on delete, 0 otherwise
 * @varia: the string environment variable property
 */
int _unsetenv(data_t *data, char *varia)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !varia)
		return (0);

	while (node)
	{
		p = begin_func(node->sr, varia);
		if (p && *p == '=')
		{
			data->env_changed = delete_node_at_index(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * _setenv - A function that initialize a new environment variable,
 *             or modify an existing one
 * @data: Structure containing potential arguments
 *
 * @varia: A string environment variable property
 * @value: A string environment variable value
 *  Return: Always 0
 */
int _setenv(data_t *data, char *varia, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!varia || !value)
		return (0);

	buff = malloc(_strlen(varia) + _strlen(value) + 2);
	if (!buff)
		return (1);
	_strcpy(buff, varia);
	_strcat(buff, "=");
	_strcat(buff, value);
	node = data->env;
	while (node)
	{
		p = begin_func(node->sr, varia);
		if (p && *p == '=')
		{
			free(node->sr);
			node->sr = buff;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(data->env), buff, 0);
	free(buff);
	data->env_changed = 1;
	return (0);
}

