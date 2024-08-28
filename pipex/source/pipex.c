#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "../includes/pipex.h"

#define BUFFER_SIZE 4096

static char	*get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

void error_exit(const char *function_name)
{
    perror(function_name);
    exit(1);
}
char	*extract_dir(char *next_dir, char *path)
{
	char	*dir;

	if (next_dir)
	{
		dir = ft_substr(path, 0, next_dir - path);
		if (!dir)
			error_exit("ft_substr");
	}
	else
	{
		dir = ft_strdup(path);
		if (!dir)
			error_exit("ft_strdup");
	}
	return (dir);
}

static char	*join_and_check_path(const char *dir, const char *command)
{
	char	*full_path;

	full_path = ft_strjoin(dir, command);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static char	*search_in_dir(char **path, const char *command)
{
	char	*dir;
	char	*next_dir;
	char	*result;

	next_dir = ft_strchr(*path, ':');
	dir = extract_dir(next_dir, *path);
	if (!dir)
		return (NULL);
	result = join_and_check_path(dir, command);
	free(dir);
	if (result)
		return (result);
	if (!next_dir)
		*path = NULL;
	else
		*path = next_dir + 1;
	return (NULL);
}

static char	*find_command_path(const char *command, char **envp)
{
	char	*path;
	char	*result;

	path = get_path(envp);
	if (!path)
		return (NULL);
	while (path && *path)
	{
		result = search_in_dir(&path, command);
		if (result)
			return (result);
	}
	return (NULL);
}

char **split_command(const char *command)
{
    char **args = ft_split(command, ' ');
    if (!args)
        error_exit("ft_split");
    return args;
}

void free_args(char **args)
{
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

void execute_command(char *command, char **envp)
{
    char *full_path;
    char *command_with_slash;
	char **args;

	args = split_command(command);
    command_with_slash = ft_strjoin("/", args[0]);
    if (!command_with_slash)
    {
        free_args(args);
        error_exit("ft_strjoin");
    }
    full_path = find_command_path(command_with_slash, envp);
    free(command_with_slash);
    if (!full_path)
    {
        ft_putstr_fd("Command not found: ", 2);
        ft_putendl_fd(args[0], 2);
        free_args(args);
        exit(1);
    }
    execve(full_path, args, envp);
    perror("execve");
    free(full_path);
    free_args(args);
    exit(1);
}

void parent_process(int *pipefd, char **argv, char **envp)
{
	int fd;
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;

	close(pipefd[0]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
		write(pipefd[1], buffer, bytes_read);
	}
	close(fd);
	close(pipefd[1]);
	wait(NULL);
}

void child_process(int *pipefd, char **envp, char *command)
{
    close(pipefd[1]);
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    
    execute_command(command, envp);
    exit(1);
}

int main(int argc, char **argv, char **envp)
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(1);
	}
	if (argc != 2) {
		ft_putendl_fd("Usage: pipex file", 2);
		exit(1);
	}
	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(1);
	}
	char *command = "wc -w";
	if (pid > 0) {
		parent_process(pipefd, argv, envp);
	} else {
		child_process(pipefd, envp, command);
	}
}
