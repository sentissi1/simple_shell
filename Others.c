#include "shell.h"

/**
 * is_chain_d_func -A function that test if current char
 * in buffer is a chain delimeter
 * @data : the parameter struct
 * @buff : the characher buffer
 * @a: @ of current position in buffer
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain_d_func(data_t *data, char *buff, size_t *a)
{
	size_t k = *a;

	if (buff[k] == '|' && buff[k + 1] == '|')
	{
		buff[k] = 0;
		k++;
		data->cmd_buf_type = CMD_OR;
	}
	else if (buff[k] == '&' && buff[k + 1] == '&')
	{
		buff[k] = 0;
		k++;
		data->cmd_buf_type = CMD_AND;
	}
	else if (buff[k] == ';')
	{
		buff[k] = 0;
		data->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*a = k;
	return (1);
}

/**
 * check_ch_func -A function that checks
 * @data: the parameter structure
 * @buff: the character buffer
 * @a: @ of current position in buf
 * @x: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_ch_func(data_t *data, char *buff, size_t *a, size_t x, size_t len)
{
	size_t j = *a;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buff[x] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buff[x] = 0;
			j = len;
		}
	}

	*a = j;
}

/**
 * replace_alias_func -A function that replaces an aliases
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias_func(data_t *data)
{
	int x;
	list_t *node;
	char *a;

	for (x = 0; x < 10; x++)
	{
		node = node_starts_with(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		a = _strchr(node->sr, '=');
		if (!a)
			return (0);
		a = _str_dupl(a + 1);
		if (!a)
			return (0);
		data->argv[0] = a;
	}
	return (1);
}

/**
 * var_replace -A function that replaces vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int var_replace(data_t *data)
{
	int x = 0;
	list_t *node;

	for (x = 0; data->argv[x]; x++)
	{
		if (data->argv[x][0] != '$' || !data->argv[x][1])
			continue;

		if (!_strcmp(data->argv[x], "$?"))
		{
			string_replace(&(data->argv[x]),
				_str_dupl(convert_num(data->status, 10, 0)));
			continue;
		}
		if (!_strcmp(data->argv[x], "$$"))
		{
			string_replace(&(data->argv[x]),
				_str_dupl(convert_num(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(data->env, &data->argv[x][1], '=');
		if (node)
		{
			string_replace(&(data->argv[x]),
				_str_dupl(_strchr(node->sr, '=') + 1));
			continue;
		}
		string_replace(&data->argv[x], _str_dupl(""));

	}
	return (0);
}

/**
 * string_replace - replaces string
 * @old: address of old string
 * @nw: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int string_replace(char **old, char *nw)
{
	free(*old);
	*old = nw;
	return (1);
}

