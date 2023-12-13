#include "shell.h"

/**
 * is_interactive - returns true if shell is in interactive mode
 * @shell: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(shell_t *shell)
{
    return (isatty(STDIN_FILENO) && shell->readfd <= 2);
}

/**
 * is_separator - checks if character is a separator
 * @ch: the char to check
 * @sep: the separator string
 * Return: 1 if true, 0 if false
 */
int is_separator(char ch, char *sep)
{
    while (*sep)
   	 if (*sep++ == ch)
   		 return (1);
    return (0);
}

/**
 *is_alpha - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if ch is alphabetic, 0 otherwise
 */

int is_alpha(int ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

/**
 *str_to_int - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int str_to_int(char *str)
{
    int i, sign = 1, flag = 0, output;
    unsigned int result = 0;

    for (i = 0;  str[i] != '\0' && flag != 2; i++)
    {
   	 if (str[i] == '-')
   		 sign *= -1;

   	 if (str[i] >= '0' && str[i] <= '9')
   	 {
   		 flag = 1;
   		 result = result * 10 + (str[i] - '0');
   	 }
   	 else if (flag == 1)
   		 flag = 2;
    }

    output = sign * result;

    return (output);
}

