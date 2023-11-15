#include "shell.h"

/**
 * loop_shell - main shell loop
 * @data: return data structure & the parameter
 * @av: the argument vectorn from the main
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(data_t *data, char **av)
{
	ssize_t t = 0;
	int builtin_ret = 0;

	while (t != -1 && builtin_ret != -2)
	{
		clear_data(data);
		if (interactive(data))
			_put_input("$ ");
		_Putchar(BUF_FLUSH);
		t = Get_Input(data);
		if (t != -1)
		{
			set_data(data, av);
			builtin_ret = find_built_in_func(data);
			if (builtin_ret == -1)
				find_cmd_func(data);
		}
		else if (interactive(data))
			_putchar('\n');
		free_data(data, 0);
	}
	Write_history_func(data);
	free_data(data, 1);
	if (!interactive(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->error_num == -1)
			exit(data->status);
		exit(data->error_num);
	}
	return (builtin_ret);
}

/**
 * find_built_in_func -A function that finds the list of built in commands
 * @data: the parameter & return data struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_built_in_func(data_t *data)
{
	int j, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit_function},
		{"env", _Env_func},
		{"help", _help_func},
		{"history", _History_fun},
		{"setenv", _New_Env_var},
		{"unsetenv", _UNSET_env_func},
		{"cd", _Cd_func},
		{"alias", _alias_func},
		{NULL, NULL}
	};

	for (j = 0; builtintbl[j].type; j++)
		if (_strcmp(data->argv[0], builtintbl[j].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[j].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd_func -A function that finds a command in PATH
 * @data: A parameter & return info struct
 *
 * Return: void
 */
void find_cmd_func(data_t *data)
{
	char *path = NULL;
	int j, h;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (j = 0, h = 0; data->arg[j]; j++)
		if (!is_delimeter(data->arg[j], " \t\n"))
			h++;
	if (!h)
		return;

	path = _Find_path(data, _Env_func(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		cmd_fork_func(data);
	}
	else
	{
		if ((interactive(data) || _Env_func(data, "PATH=")
			|| data->argv[0][0] == '/') && _is_cmd(data, data->argv[0]))
			cmd_fork_func(data);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			error_print_msg(data, "Not Found\n");
		}
	}
}

/**
 * cmd_fork_func -A function that forks a an exec thread to run cmd
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void cmd_fork_func(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, data->argv, Get_env(data)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				error_print_msg(data, "Permission Denied\n");
		}
	}
}

