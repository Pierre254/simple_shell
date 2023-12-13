#include "shell.h"

/**
 * buffer_input - buffers chained commands
 * @info: parameter struct
 * @input: address of input
 * @size: address of size var
 *
 * Return: bytes read
 */
ssize_t buffer_input(info_t *info,
		     char **input,
		     size_t *size)
{
	ssize_t r = 0;
	size_t size_p = 0;

	if (!*size) /* if nothing left in the input, fill it */
	{
		free(*input);
		*input = NULL;
		signal(SIGINT,
		       sigint_handler);
#if USE_GETLINE
		r = getline(input,
			     &size_p,
			     stdin);
#else
		r = _getline(info,
			      input,
			      &size_p);
#endif
		if (r > 0)
		{
			if ((*input)[r - 1] == '\n')
			{
				(*input)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*input);
			build_history_list(info,
					   *input,
					   info->histcount++);
			/* if (_strchr(*input, ';')) is this a command chain? */
			{
				*size = r;
				info->cmd_input = input;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *input; /* the ';' command chain input */
	static size_t i, j, size;
	ssize_t r = 0;
	char **input_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = buffer_input(info, &input, &size);
	if (r == -1) /* EOF */
		return (-1);
	if (size)    /* we have commands left in the chain input */
	{
		j = i; /* init new iterator to current input position */
		p = input + i; /* get pointer for return */

		check_chain(info, input, &j, i, size);
		while (j < size) /* iterate to semicolon or end */
		{
			if (is_chain(info, input, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= size) /* reached end of input? */
		{
			i = size = 0; /* reset position and size */
			info->cmd_input_type = CMD_NORM;
		}

		*input_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*input_p = input; /* else not a chain, pass back input from _getline() */
	return (r); /* return length of input from _getline() */
}

/**
 * read_input - reads an input
 * @info: parameter struct
 * @input: input
 * @i: size
 *
 * Return: r
 */
ssize_t read_input(info_t *info, char *input, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, input, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to input, preallocated or NULL
 * @length: size of preallocated ptr input if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char input[READ_BUF_SIZE];
	static size_t i, size;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == size)
		i = size = 0;

	r = read_input(info, input, &size);
	if (r == -1 || (r == 0 && size == 0))
		return (-1);

	c = _strchr(input + i, '\n');
	k = c ? 1 + (unsigned int)(c - input) : size;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, input + i, k - i);
	else
		_strncpy(new_p, input + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
