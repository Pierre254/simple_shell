#include "shell.h"

/* Main entry point */
int main(int argc, char **argv)
{
	info_t info[] = { INFO_INIT };
	int fd = STDIN_FILENO;

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
				fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
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
