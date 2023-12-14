#include "shell.h"

<<<<<<< HEAD
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));
=======
/* Main entry point */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = STDIN_FILENO;
>>>>>>> 2703a8a5aeff280a4a0e27f00d775372ae09f507

	/* Check if there is an argument */
	if (argc == 2)
	{
		/* Open the argument file for reading */
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			/* Handle the error according to the errno value */
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
<<<<<<< HEAD
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
=======
				fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
>>>>>>> 2703a8a5aeff280a4a0e27f00d775372ae09f507
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		/* Set the read file descriptor to the opened file */
		info->readfd = fd;
	}

	/* Populate the environment list */
	populate_env_list(info);

	/* Read the history from the file */
	read_history(info);

	/* Start the shell */
	hsh(info, argv);

	/* Return success */
	return (EXIT_SUCCESS);
}
