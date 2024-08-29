#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "../includes/pipex.h"

#define BUFFER_SIZE 4096

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
            return (NULL);
    }
    else
    {
        dir = ft_strdup(path);
        if (!dir)
            return (NULL);
    }
    return dir;
}

static char *join_and_check_path(const char *dir, const char *command)
{
    char *full_path;
    char *temp;

    temp = ft_strjoin(dir, "/");
    if (!temp)
        return (NULL);
    full_path = ft_strjoin(temp, command);
    free(temp);
    if (!full_path)
        return (NULL);
    if (access(full_path, X_OK) == 0)
        return (full_path);
    free(full_path);
    return (NULL);
}

static char *find_command_path(const char *command, char **envp)
{
    char *path;
    char *dir;
    char *next_dir;
    char *result;

    path = get_path(envp);
    while (path && *path)
    {
        next_dir = ft_strchr(path, ':');
        dir = extract_dir(next_dir, path);
        if (!dir)
            return (NULL);
        result = join_and_check_path(dir, command);
        free(dir);
        if (result)
            return (result);
		if (!next_dir)
			break ;
        path = next_dir + 1;
    }
    return (NULL);
}

int error_return(const char *function_name, int error_code)
{
    perror(function_name);
    return error_code;
}

int execute_command(char *command, char **envp)
{
    char *full_path;
    char ** args;

    args = ft_split(command, ' ');
    if (!args)
        return (error_return("split_command", EXIT_FAILURE));
    full_path = find_command_path(args[0], envp);
    if (!full_path)
    {
        ft_putstr_fd("Command not found: ", 2);
        ft_putendl_fd(args[0], 2);
        free_args(args);
        return (127);  // Return "command not found" status
    }
    
    execve(full_path, args, envp);
    
    // If execve returns, it means it failed
    free(full_path);
    free_args(args);
    return (error_return("execve", 126));  // Return "command invocation failed" status
}

void child_process(int *pipefd, char **envp, char *command)
{
    int status;

    close(pipefd[1]);
    if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		    perror("dup2");
    		exit(EXIT_FAILURE);
	}
    close(pipefd[0]);
    status = execute_command(command, envp);
    exit(status);
}

int parent_process(int *pipefd, char *input_file, pid_t child_pid)
{
    int     fd;
    char    buffer[BUFFER_SIZE];
    ssize_t bytes_read;
    int     status;

    close(pipefd[0]);
    fd = open(input_file, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        close(pipefd[1]);
        waitpid(child_pid, NULL, 0);
        return (EXIT_FAILURE);
    }

    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (write(pipefd[1], buffer, bytes_read) == -1)
        {
            perror("write");
            break;
        }
    }

    close(fd);
    close(pipefd[1]);
    waitpid(child_pid, &status, 0);
    if (WIFEXITED(status))
        return (WEXITSTATUS(status));
    return (EXIT_FAILURE);
}

int main(int argc, char ** argv, char **envp)
{
    int     pipefd[2];
    pid_t   pid;
    char    *command;

    if (argc != 2)
    {
        ft_putendl_fd("Usage: pipex file", 2);
        return (EXIT_FAILURE);
    }

    if (pipe(pipefd) == -1)
        return (error_return("pipe", EXIT_FAILURE));

    pid = fork();
    if (pid == -1)
        return (error_return("fork", EXIT_FAILURE));

    command = "wcWW -w";
    if (pid == 0)
        child_process(pipefd, envp, command);
    else
        return (parent_process(pipefd, argv[1], pid));
}