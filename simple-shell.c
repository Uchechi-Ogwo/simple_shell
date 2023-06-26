#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/**
 * main - Program that runs shell command.
 *
 * Return: Always 0.
 */
int main(int argc, char *argv[], char **env)
{
	char *buff = NULL, *prompt = "$";
	size_t buff_size = 0;
	ssize_t bytes;
	pid_t hpid;
	int hstatus;
	bool from_pipe = false;
	struct stat statbuf;

	while (1 && !from_pipe)
	{
		if (isatty(STDIN_FILENO) == 0)
			from_pipe = true;

		write(STDOUT_FILENO, prompt, 2);

		bytes = getline(&buff, &buff_size, stdin);
		if (bytes == -1)
		{
			perror("Error (getline)");
			free(buff);
			exit(EXIT_FAILURE);
		}

		if (buff[bytes - 1] == '\n')
			buff[bytes - 1] = '\0';

		hpid = fork();
		if (hpid == -1)
		{
			perror("Error (fork)");
			exit(EXIT_FAILURE);
		}

		if (hpid == 0)
			_execute(buff, &statbuf, env);

		if (waitpid(hpid, &hstatus, 0) == -1)
		{
			perror("Error (wait)");
			exit(EXIT_FAILURE);
		}
	}

	free(buff);
	return (0);
}

/**
 * _execute - Execute the shell command.
 * @arguments: The command arguments.
 * @statbuf: Pointer to the stat struct.
 * @envp: The environment variables.
 *
 * Return: Void.
 */
void _execute(char *arguments, struct stat *statbuf, char **envp)
{
	int argc;
	char **argv;
	char *exe;

	argv = split_string(arguments, " ", &argc);

	if (!check_file_status(argv[0], statbuf))
	{
		perror("Error (file status)");
		exit(EXIT_FAILURE);
	}

	execve(argv[0], argv, envp);
	perror("Error (execve)");
	exit(EXIT_FAILURE);
}

/**
 * check_file_status - Check the status of the file.
 * @pathname: The file path.
 * @statbuf: Pointer to the stat struct.
 *
 * Return: True if file exists, false otherwise.
 */
bool check_file_status(char *pathname, struct stat *statbuf)
{
	int stat_return;

	stat_return = stat(pathname, statbuf);
	if (stat_return == 0)
		return (true);

	return (false);
}

