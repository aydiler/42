/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_map_flood_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 22:11:58 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/19 22:28:27 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	flood_fill(t_game *game, int **visited, int x, int y)
{
	if (x < 0 || x >= game->plot.length || y < 0 || y >= game->plot.height)
		return ;
	if (visited[y][x] || game->plot.map[y][x] == '1')
		return ;
	visited[y][x] = 1;
	flood_fill(game, visited, x + 1, y);
	flood_fill(game, visited, x - 1, y);
	flood_fill(game, visited, x, y + 1);
	flood_fill(game, visited, x, y - 1);
}

static int	**allocate_visited(t_game *game)
{
	int	**visited;
	int	i;

	visited = malloc(game->plot.height * sizeof(int *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < game->plot.height)
	{
		visited[i] = ft_calloc(game->plot.length, sizeof(int));
		if (!visited[i])
		{
			while (i > 0)
				free(visited[--i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

static t_point	find_start(t_game *game)
{
	t_point	start;
	int		i;
	int		j;

	start.x = -1;
	start.y = -1;
	i = -1;
	while (++i < game->plot.height)
	{
		j = -1;
		while (++j < game->plot.length)
		{
			if (game->plot.map[i][j] == 'P')
			{
				start.x = j;
				start.y = i;
				return (start);
			}
		}
	}
	return (start);
}

static int	check_collectibles(t_game *game, int **visited)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->plot.height)
	{
		j = -1;
		while (++j < game->plot.length)
		{
			if (game->plot.map[i][j] == 'C' && !visited[i][j])
				return (0);
		}
	}
	return (1);
}

int	are_collectibles_reachable(t_game *game)
{
	int		**visited;
	t_point	start;
	int		result;
	int		i;

	visited = allocate_visited(game);
	if (!visited)
		return (0);
	start = find_start(game);
	if (start.x == -1 || start.y == -1)
	{
		i = 0;
		while (i < game->plot.height)
			free(visited[i++]);
		free(visited);
		return (0);
	}
	flood_fill(game, visited, start.x, start.y);
	result = check_collectibles(game, visited);
	i = 0;
	while (i < game->plot.height)
		free(visited[i++]);
	free(visited);
	return (result);
}
