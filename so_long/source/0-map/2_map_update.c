/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_map_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:28:24 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/19 15:27:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	read_map(t_game *game, int fd);
static void	allocate_map_line(t_game *game, char ***map,
				int *height, char *line);

void	init_map(t_game *game, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nInvalid file\n");
		exit(1);
	}
	read_map(game, fd);
	line_validation(game->plot.map, game);
	game->plot.length = ft_strlen(game->plot.map[0]);
	close(fd);
}

static void	allocate_map_line(t_game *game, char ***map, \
	int *height, char *line)
{
	char	*new_line;

	if (line[ft_strlen(line) - 1] != '\n')
	{
		new_line = ft_strjoin(line, "\n");
		if (!new_line)
			endgame("Memory allocation failed!", game, error);
	}
	else
	{
		new_line = ft_strdup(line);
		if (!new_line)
			endgame("Memory allocation failed!", game, error);
	}
	*map = ft_realloc(*map, *height * sizeof(char *),
			(*height + 2) * sizeof(char *));
	if (!*map)
		endgame("Memory allocation failed!", game, error);
	(*map)[*height] = new_line;
	(*map)[*height + 1] = NULL;
	(*height)++;
	free(line);
}

static void	read_map_lines(t_game *game, int fd, char ***map, int *height)
{
	char	*line;
	size_t	total_len;

	total_len = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		allocate_map_line(game, map, height, line);
		total_len += ft_strlen((*map)[*height - 1]);
		line = get_next_line(fd);
	}
	game->plot.length = total_len / *height;
}

static void	concatenate_map(t_game *game, char **map, int height)
{
	char	*string_map;
	int		i;
	size_t	total_len;

	total_len = height * game->plot.length;
	string_map = malloc(total_len + 1);
	if (string_map == NULL)
		endgame("Memory allocation failed!", game, error);
	string_map[0] = '\0';
	i = 0;
	while (i < height)
	{
		ft_strlcat(string_map, map[i], total_len + 1);
		i++;
	}
	game->i = start_counter(string_map, game);
	free(string_map);
}

static void	read_map(t_game *game, int fd)
{
	char	**map;
	int		height;

	map = NULL;
	height = 0;
	read_map_lines(game, fd, &map, &height);
	game->plot.map = map;
	game->plot.height = height;
	concatenate_map(game, map, height);
}
