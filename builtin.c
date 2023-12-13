#include "shell.h"

/**
 * _myexit - exits the shell
 * @info: pointer to structure containing arguments and other variables
 * Return: -2 if info.argv[0] == "exit", 1 if invalid exit argument, 0 otherwise
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* check if there is an exit argument */
	{
		exitcheck = _erratoi(info->argv[1]); /* convert argument to integer */
		if (exitcheck == -1) /* check if conversion failed */
		{
			info->status = 2; /* set status to 2 */
			print_error(info, "Illegal number: "); /* print error message */
			_eputs(info->argv[1]); /* print argument */
			_eputchar('\n'); /* print newline */
			return (1); /* return 1 */
		}
		info->err_num = exitcheck; /* set err_num to exit argument */
		return (-2); /* return -2 to indicate exit */
	}
	info->err_num = -1; /* set err_num to -1 */
	return (-2); /* return -2 to indicate exit */
}

/**
 * _mycd - changes the current directory of the process
 * @info: pointer to structure containing arguments and other variables
 * Return: 0 on success, 1 on failure
 */
int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024); /* get current working directory */
	if (!s) /* check if getcwd failed */
		_puts("Error: getcwd failed\n"); /* print error message */
	if (!info->argv[1]) /* check if no argument is given */
	{
		dir = _getenv(info, "HOME="); /* get home directory from environment */
		if (!dir) /* check if home directory is not found */
			chdir_ret = chdir((dir = _getenv(info, "PWD=")) ? dir : "/"); /* use current directory or root directory */
		else
			chdir_ret = chdir(dir); /* use home directory */
	}
	else if (_strcmp(info->argv[1], "-") == 0) /* check if argument is "-" */
	{
		if (!_getenv(info, "OLDPWD=")) /* check if old directory is not found */
		{
			_puts(s); /* print current directory */
			_putchar('\n'); /* print newline */
			return (1); /* return 1 */
		}
		_puts(_getenv(info, "OLDPWD=")); /* print old directory */
		_putchar('\n'); /* print newline */
		chdir_ret = chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/"); /* use old directory or root directory */
	}
	else /* otherwise */
		chdir_ret = chdir(info->argv[1]); /* use argument as directory */
	if (chdir_ret == -1) /* check if chdir failed */
	{
		print_error(info, "can't cd to "); /* print error message */
		_eputs(info->argv[1]); /* print argument */
		_eputchar('\n'); /* print newline */
		return (1); /* return 1 */
	}
	else /* otherwise */
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD=")); /* update old directory in environment */
		_setenv(info, "PWD", getcwd(buffer, 1024)); /* update current directory in environment */
	}
	return (0); /* return 0 */
}

/**
 * _myhelp - displays help information for built-in commands
 * @info: pointer to structure containing arguments and other variables
 * Return: 0 on success, 1 on failure
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv; /* get arguments array */
	if (!arg_array[1]) /* check if no argument is given */
	{
		_puts("Usage: help [BUILTIN]\n"); /* print usage message */
		_puts("Displays information about built-in commands.\n"); /* print description */
		_puts("BUILTIN: the name of a built-in command\n"); /* print argument explanation */
		return (0); /* return 0 */
	}
	else /* otherwise */
	{
		/* TODO: implement help for each built-in command */
		_puts("Sorry, help for this command is not yet implemented.\n"); /* print placeholder message */
		return (1); /* return 1 */
	}
}
