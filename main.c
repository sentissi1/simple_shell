#include "shell.h"

/**
 * main - The entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	data_t data[] = { INFO_INIT };
	int DF = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (DF)
		: "r" (DF));

	if (ac == 2)
	{
		DF = open(av[1], O_RDONLY);
		if (DF == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_Put(av[0]);
				_Put(": 0: Can't open ");
				_Put(av[1]);
				_Putchar('\n');
				_Putchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->readfd = DF;
	}
	_Env_List(data);
	Read_history_func(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}

