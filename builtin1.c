#include "shell.h"

/* Show history - displays the history list, one command by line, preceded
 * with line numbers, starting at 0.
 * @shell: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int show_history(shell_t *shell)
{
	print_list(shell->history);
	return (0);
}

/* Remove alias - removes an alias from the list
 * @shell: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int remove_alias(shell_t *shell, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(shell->alias),
		get_node_index(shell->alias, node_starts_with(shell->alias, str, -1)));
	*p = c;
	return (ret);
}

/* Add alias - adds an alias to the list
 * @shell: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int add_alias(shell_t *shell, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (remove_alias(shell, str));

	remove_alias(shell, str);
	return (add_node_end(&(shell->alias), str, 0) == NULL);
}

/* Display alias - displays an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int display_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/* Manage alias - mimics the alias builtin (man alias)
 * @shell: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int manage_alias(shell_t *shell)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (shell->argc == 1)
	{
		node = shell->alias;
		while (node)
		{
			display_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; shell->argv[i]; i++)
	{
		p = _strchr(shell->argv[i], '=');
		if (p)
			add_alias(shell, shell->argv[i]);
		else
			display_alias(node_starts_with(shell->alias, shell->argv[i], '='));
	}

	return (0);
}
