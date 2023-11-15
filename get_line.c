#include "shell.h"

/**
 * input_buff -Az fonction that buffers chained commands
 * @data: parameter struct
 * @buff: address of buffer
 * @length: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(data_t *data, char **buff, size_t *length)
{
	ssize_t x = 0;
	size_t length_b = 0;

	if (!*length) /* if nothing left in the buffer, fill it */
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buff, &length_b, stdin);
#else
		x = _getline(data, buff, &length_b);
#endif
		if (x > 0)
		{
			if ((*buff)[x - 1] == '\n')
			{
				(*buff)[x - 1] = '\0';
				x--;
			}
			data->linecount_flag = 1;
			delete_comments(*buff);
			Build_history_func(data, *buff, data->histcount++);

			{
				*length = x;
				data->cmd_buf = buff;
			}
		}
	}
	return (x);
}

/**
 * Get_Input -A function that gets a line minus the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t Get_Input(data_t *data)
{
	static char *buff;
	static size_t x, y, length;
	ssize_t z = 0;
	char **buff_p = &(data->arg), *p;

	_putchar(BUF_FLUSH);
	z = input_buff(data, &buff, &length);
	if (z == -1)
		return (-1);
	if (length)
	{
		y = x;
		p = buff + x;

		check_ch_func(data, buff, &y, x, length);
		while (y < length)
		{
			if (is_chain_d_func(data, buff, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= length)
		{
			x = length = 0;
			data->cmd_buf_type = CMD_NORM;
		}

		*buff_p = p;
		return (_strlen(p));
	}

	*buff_p = buff;
	return (z);
}

/**
 * read_buffer -A functin that reads a buffer
 * @data: parameter struct
 * @buff: buffer
 * @sz: size
 *
 * Return: o
 */
ssize_t read_buffer(data_t *data, char *buff, size_t *sz)
{
	ssize_t o = 0;

	if (*sz)
		return (0);
	o = read(data->readfd, buff, READ_BUF_SIZE);
	if (o >= 0)
		*sz = o;
	return (o);
}

/**
 * _getline -A funcction that gets the next line of input from STD input
 * @data: parameter struct
 * @pontr: address of pointer to buffer, pre-located or null
 * @len: size of preallocated ptr buffer if not null
 *
 * Return: sv
 */
int _getline(data_t *data, char **pontr, size_t *len)
{
	static char buff[READ_BUF_SIZE];
	static size_t i, leng;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *pontr;
	if (p && len)
		s = *len;
	if (i == leng)
		i = leng = 0;

	r = read_buffer(data, buff, &leng);
	if (r == -1 || (r == 0 && leng == 0))
		return (-1);

	c = _strchr(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : leng;
	new_p = _realloc_func(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + i, k - i);
	else
		_strncpy(new_p, buff + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (len)
		*len = s;
	*pontr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sgn_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sgn_num)
{
	_put_input("\n");
	_put_input("$ ");
	_putchar(BUF_FLUSH);
}

