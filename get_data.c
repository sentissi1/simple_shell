#include "shell.h"

/**
 * clear_data -A function that initializes data_t struct
 * @data: struct address
 */
void clear_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * set_data -A function that initializes data_t struct
 * @data: struct address
 * @av: arg vector
 */
void set_data(data_t *data, char **av)
{
	int x = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtoi(data->arg, " \t");
		if (!data->argv)
		{

			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _str_dupl(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (x = 0; data->argv && data->argv[x]; x++)
			;
		data->argc = x;

		replace_alias_func(data);
		var_replace(data);
	}
}

/**
 * free_data -A function that frees data_t struct spots
 * @data: struct address
 * @tout: true if freeing all spots
 */
void free_data(data_t *data, int tout)
{
	free_func(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (tout)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			free_list(&(data->env));
		if (data->history)
			free_list(&(data->history));
		if (data->alias)
			free_list(&(data->alias));
		free_func(data->environ);
			data->environ = NULL;
		Bfree((void **)data->cmd_buf);
		if (data->readfd > 2)
			close(data->readfd);
		_putchar(BUF_FLUSH);
	}
}

