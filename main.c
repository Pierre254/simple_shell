#include "shell.h"

// Enable some compiler optimizations
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("inline")
#pragma GCC optimize("tree-vectorize")

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(register int ac, register char **av)
{
	info_t info[] = { INFO_INIT };
	register int fd = 2;

	asm ("mov %1, %0\n\t"
	     "add $3, %0"
	     : "=r" (fd)
	     : "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				// Use formatted output instead of string concatenation
				fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
