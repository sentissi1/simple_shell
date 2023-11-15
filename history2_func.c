#include "shell.h"

/**
 * Get_history_func -A function that gets the history file
 * @data: parameter struct
 *
 * Return: allocated string containg history file
 */

char *Get_history_func(data_t *data)
{
	char *buff, *dir;

	dir = _Env_func(data, "HOME=");
	if (!dir)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, dir);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * Write_history_func -A function that creates a file, or appends to an existing file
 * @data: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int Write_history_func(data_t *data)
{
	ssize_t DF;
	char *filename = Get_history_func(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	DF = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if ( DF -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_Put_str_input(node->sr, DF);
		_PutDf('\n', DF);
	}
	_PutDf(BUF_FLUSH, DF);
	close(DF);
	return (1);
}

/**
 * Read_history_func -A function that reads history from file
 * @data: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int Read_history_func(data_t *data)
{
	int x, last = 0, linecounter = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *filename = Get_history_func(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (!buff)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (x = 0; x < fsize; x++)
		if (buff[x] == '\n')
		{
			buff[x] = 0;
			Build_history_func(data, buff + last, linecounter++);
			last = x + 1;
		}
	if (last != x)
		Build_history_func(data, buff + last, linecounter++);
	free(buff);
	data->histcount = linecounter;
	while (data->histcount-- >= HIST_MAX)
		delete_node_at_index(&(data->history), 0);
	Re_number_hst_func(data);
	return (data->histcount);
}

/**
 * Build_history_func -A function that build history list
 * @data: A structure could contain potential arguments. Used to maintain
 * @buff: buffer
 * @linecounter: the history linecount, histcount
 *
 * Return: Always 0
 */
int Build_history_func(data_t *data, char *buff, int linecounter)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	add_node_end(&node, buff, linecounter);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * Re_number_hst_func -a function that renumbers the history list  changes
 * @data: A structure that could containe potential args. Used to maintain
 *
 * Return: History count
 */
int Re_number_hst_func(data_t *data)
{
	list_t *node = data->history;
	int x = 0;

	while (node)
	{
		node->nm = x++;
		node = node->next;
	}
	return (data->histcount = x);
}

