#include "shell.h"

/**
 * _exit_function - exits the shell
 * @data: A structure contain potential arguments
 *
 *Return: exits with a given exit statu
 */
int _exit_function(data_t *data)
{
	int exit_check;

	if (data->argv[1])
	{
		exit_check = _convert_func(data->argv[1]);
		if (exit_check == -1)
		{
			data->status = 2;
			error_print_msg(data, "Invalid Number: ");
			_Put(data->argv[1]);
			_Putchar('\n');
			return (1);
		}
		data->error_num = _convert_func(data->argv[1]);
		return (-2);
	}
	data->error_num = -1;
	return (-2);
}

/**
 * _Cd_func - A function that changes the current directory of the process
 * @data:A structure that contain potential arguments
 *
 *Return: Always 0
 */
int _Cd_func(data_t *data)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_put_input("TODO: >>Get cwd failure message HERE<<\n");
	if (!data->argv[1])
	{
		dir = _Env_func(data, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _Env_func(data, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "_") == 0)
	{
		if (!_Env_func(data, "oldPWD="))
		{
			_put_input(s);
			_putchar('\n');
			return (1);
		}
		_put_input(_Env_func(data, "oldPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _Env_func(data, "oldPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		error_print_msg(data, "can't Change Directory to ");
		_Put(data->argv[1]), _Putchar('\n');
	}
	else
	{
		_setenv(data, "oldPWD", _Env_func(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _help_func -A function that changes the current directory of the process
 * @data:a structure that could contain potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _help_func(data_t *data)
{
	char **argument_array;

	argument_array = data->argv;
	_put_input("When fun not yet implimented it help to call works\n");
	if (0)
		_put_input(*argument_array);
	return (0);
}

