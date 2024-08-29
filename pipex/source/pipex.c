#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "../includes/pipex.h"

void error_exit(const char *function_name)
{
	perror(function_name);
	exit(EXIT_FAILURE);
}

void	execute_command(char *command, char ** envp)
{
	char	*full_path;
	char	**args;

	args = ft_split(command, ' ');
	if (!args)
		error_exit("ft_split");
	full_path = find_command_path(args[0], envp);
	if (!full_path)
	{
		free_args(args);
		error_exit("command not found");
	}
	if (execve(full_path, args, envp) == -1)
		error_exit("execve");
}

void	child_process(int *pipefd, char *command, char *output_file, char **envp)
{
	int	fd;

	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2");
	close(pipefd[0]);
	fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_exit("open");
	if (dup2(fd, STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(fd);
	execute_command(command, envp);
}

void	parent_process(int *pipefd, char *input_file, char *command, char **envp)
{
	int		fd;

	fd = open(input_file, O_RDONLY);
	if (fd == -1)
		error_exit("open");
	if (dup2(fd, STDIN_FILENO) == -1)
		error_exit("dup2");
	close(fd);
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		error_exit("dup2");
	close(pipefd[1]);
	execute_command(command, envp);
}

int	main(int argc, char **argv, char ** envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
	if (pid == 0)
		child_process(pipefd, argv[3], argv[4], envp);
	else
	{
		parent_process(pipefd, argv[1], argv[2], envp);
		waitpid(pid, NULL, 0);
	}
	return (0);
}