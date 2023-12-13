#include "shell.h"

/**
 * exit_shell - exits the shell
 * @shell: Structure containing potential arguments. Used to maintain
 *      	constant function prototype.
 *  Return: exits with a given exit status
 *     	(0) if shell.argv[0] != "exit"
 */
int exit_shell(shell_t *shell)
{
    int exit_status;

    if (shell->argv[1])  /* If there is an exit argument */
    {
   	 exit_status = str_to_int(shell->argv[1]);
   	 if (exit_status == -1)
   	 {
   		 shell->status = 2;
   		 print_error(shell, "Illegal number: ");
   		 _eputs(shell->argv[1]);
   		 _eputchar('\n');
   		 return (1);
   	 }
   	 shell->err_num = exit_status;
   	 return (-2);
    }
    shell->err_num = -1;
    return (-2);
}

/**
 * change_dir - changes the current directory of the process
 * @shell: Structure containing potential arguments. Used to maintain
 *      	constant function prototype.
 *  Return: Always 0
 */
int change_dir(shell_t *shell)
{
    char *s, *dir, buffer[1024];
    int chdir_ret;

    s = getcwd(buffer, 1024);
    if (!s)
   	 _puts("TODO: >>getcwd failure emsg here<<\n");
    if (!shell->argv[1])
    {
   	 dir = _getenv(shell, "HOME=");
   	 if (!dir)
   		 chdir_ret = chdir("/");
   	 else
   		 chdir_ret = chdir(dir);
    }
    else if (_strcmp(shell->argv[1], "-") == 0)
    {
   	 if (!_getenv(shell, "OLDPWD="))
   	 {
   		 _puts(s);
   		 _putchar('\n');
   		 return (1);
   	 }
   	 _puts(_getenv(shell, "OLDPWD=")), _putchar('\n');
   	 chdir_ret = chdir(_getenv(shell, "OLDPWD="));
    }
    else
   	 chdir_ret = chdir(shell->argv[1]);
    if (chdir_ret == -1)
    {
   	 print_error(shell, "can't cd to ");
   	 _eputs(shell->argv[1]), _eputchar('\n');
    }
    else
    {
   	 _setenv(shell, "OLDPWD", _getenv(shell, "PWD="));
   	 _setenv(shell, "PWD", getcwd(buffer, 1024));
    }
    return (0);
}

/**
 * show_help - shows the help message for the shell
 * @shell: Structure containing potential arguments. Used to maintain
 *      	constant function prototype.
 *  Return: Always 0
 */
int show_help(shell_t *shell)
{
    char **arg_array;

    arg_array = shell->argv;
    _puts("help call works. Function not yet implemented \n");
    if (0)
   	 _puts(*arg_array); /* temp att_unused workaround */
    return (0);
}
