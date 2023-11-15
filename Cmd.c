#include "shell.h"

/**
 * _is_cmd -A function that determines if a file is an executable command
 * @data: the data structure
 * @pth: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int _is_cmd(data_t *data, char *pth)
{
	struct stat st;

	(void)data;
	if (!pth || stat(pth, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * _duplicate_char -A function that duplicates characters
 * @pthsr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new BBuffer
 */
char *_duplicate_char(char *pthsr, int start, int stop)
{
	static char buf[1024];
	int j = 0, h = 0;

	for (h = 0, j = start; j < stop; j++)
		if (pthsr[j] != ':')
			buf[h++] = pthsr[j];
	buf[h] = 0;
	return (buf);
}

/**
 * _Find_path -A function that finds this cmd in the PATH string
 * @data: the data structure
 * @pthsr: the PATH string
 * @Cmd: the cmd to find
 *
 * Return: full path of cmd if found or 0
 */
char *_Find_path(data_t *data, char *pthsr, char *Cmd)
{
	int j = 0, curr_pos = 0;
	char *path;

	if (!pthsr)
		return (NULL);
	if ((_strlen(Cmd) > 2) && begin_func(Cmd, "./"))
{
		if (_is_cmd(data, Cmd))
			return (Cmd);
	}
	while (1)
	{
		if (!pthsr[j] || pthsr[j] == ':')
		{
			path = _duplicate_char(pthsr, curr_pos, j);
			if (!*path)
				_strcat(path, Cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, Cmd);
			}
			if (_is_cmd(data, path))
				return (path);
			if (!pthsr[j])
				break;
			curr_pos = j;
		}
		j++;
	}
	return (NULL);
}


