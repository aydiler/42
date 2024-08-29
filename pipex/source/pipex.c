#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "../includes/pipex.h"

#define BUFFER_SIZE 4096

int error_return(const char *function_name, int error_code)
{
    perror(function_name);
    return error_code;
}

void error_exit(const char *function_name)
{
	perror(function_name);
	exit(EXIT_FAILURE);
}

void free_args(char **args)
{
    for (int i = 0; args[i]; i++)
        free(args[i]);
    free(args);
}

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

char *extract_dir(char *next_dir, char *path)
{
    char *dir;

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
    return dir;
}

static char	*find_command_path(const char *command, char **envp)
{
	char	*path;
	char	*dir;
	char	*next_dir;
	char	*full_path;
	char	*temp;

	path = get_path(envp);
	if (!path)
		return (NULL);
	while (*path)
	{
		next_dir = ft_strchr(path, ':');
		dir = extract_dir(next_dir, path);
		if (!dir)
			return (NULL);
		temp = ft_strjoin(dir, "/");
		free(dir);
		if (!temp)
			return (NULL);
		full_path = ft_strjoin(temp, command);
		free(temp);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		if (!next_dir)
			break;
		path = next_dir + 1;
	}
	return (NULL);
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
	{
		free(full_path);
		free_args(args);
		error_exit("execve");
	}	
	free(full_path);
	free_args(args);
	exit(EXIT_FAILURE);
}

void child_process(int *pipefd, char **envp, char *command)
{
    int status;

    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
		error_exit("dup2");			
    close(pipefd[0]);
    execute_command(command, envp);
    exit(EXIT_FAILURE);
}

void	parent_process(int *pipefd, char *input_file)
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;

	close(pipefd[0]);
	fd = open(input_file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		close(pipefd[1]);
		return ;
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (write(pipefd[1], buffer, bytes_read) == -1)
			break ;
	}
	close(fd);
	close(pipefd[1]);
}

int	main(int argc, char **argv, char ** envp)
{
	int		pipefd[2];
	pid_t	pid;
	char	*command;

	if (argc != 2)
	{
		ft_putstr_fd("Usage: pipex file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (pipe(pipefd) == -1)
		error_exit("pipe");
	pid = fork();
	if (pid == -1)
		error_exit("fork");
		
	command = "wcWW -w";
	if (pid == 0)
		child_process(pipefd, envp, command);
	else
	{
		parent_process(pipefd, argv[1]);
		waitpid(pid, NULL, 0);
	}
}