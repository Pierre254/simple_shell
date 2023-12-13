#include "shell.h"

/**
<<<<<<< HEAD
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
=======
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

>>>>>>> 01e1ce4a1162ec31a11dad85d73d805d8f164d66
