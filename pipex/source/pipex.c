#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include "../includes/pipex.h"

#define BUFFER_SIZE 4096

static char	*find_command_path(const char *command, char **envp)
{
	char	*path;
	char	*dir;
	char	*full_path;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	path = envp[i] + 5;
	while (path && *path)
	{
		dir = ft_substr(path, 0, ft_strchr(path, ':') - path);
		full_path = ft_strjoin(dir, "/");
		full_path = ft_strjoin(full_path, command);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		free(dir);
		path = ft_strchr(path, ':');
		if (path)
			path++;
	}
	return (NULL);
}

void	execute_command(char *command, char **envp)
{
	char	**args;
	char	*full_path;

	args = ft_split(command, ' ');
	if (!args)
	{
		perror("ft_split");
		exit(1);
	}
	full_path = find_command_path(args[0], envp);
	if (!full_path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(args[0], 2);
		exit(1);
	}
	execve(full_path, args, envp);
	perror("execve");
	free(full_path);
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

    // Read from file and write to pipe
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0) {
        write(pipefd[1], buffer, bytes_read);
    }

    close(fd);
    close(pipefd[1]);  // Close write end to signal EOF to the child

    wait(NULL);
}

void child_process(int *pipefd, char **envp)
{
    close(pipefd[1]);  // Close unused write end

    // Redirect stdin to read end of pipe
    dup2(pipefd[0], 0);
    close(pipefd[0]);

    // Execute wc -l
    char *args[] = {"wc", "-w", NULL};
    execute_command("wc -w", envp);
}

int main(int argc, char **argv, char **envp)
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }

    if (pid > 0) {
        parent_process(pipefd, argv, envp);
    } else {
        child_process(pipefd, envp);
    }

    return 0;
}