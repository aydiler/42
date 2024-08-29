#include "../includes/pipex.h"

void free_args(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
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

static char	*extract_dir(char *next_dir, char *path)
{
	char	*dir;

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
	return (dir);
}

static char	*find_command_path_helper(char *dir, const char *command)
{
	char	*temp;
	char	*full_path;

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
	return (NULL);
}

char	*find_command_path(const char *command, char **envp)
{
	char	*path;
	char	*dir;
	char	*next_dir;
	char	*full_path;

	path = get_path(envp);
	if (!path)
		return (NULL);
	while (*path)
	{
		next_dir = ft_strchr(path, ':');
		dir = extract_dir(next_dir, path);
		if (!dir)
			return (NULL);
		full_path = find_command_path_helper(dir, command);
		if (full_path)
			return (full_path);
		if (!next_dir)
			break ;
		path = next_dir + 1;
	}
	return (NULL);
}