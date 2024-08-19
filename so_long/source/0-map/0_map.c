/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 21:29:12 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/08/20 00:26:00 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	check_map_maker(t_game *game, int y, int x)
{
	if (game->plot.map[y][x] == 'E')
	{
		game->portal.x = x * SPRITE_SIZE;
		game->portal.y = y * SPRITE_SIZE;
		mlx_put_image_to_window(game->mlx_pointer, game->window_pointer, \
		game->portal.ptr, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
	}
	else if (game->plot.map[y][x] == '1')
		mlx_put_image_to_window(game->mlx_pointer, game->window_pointer, \
		game->wall.ptr, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
	else if (game->plot.map[y][x] == 'C')
	{
		mlx_put_image_to_window(game->mlx_pointer, game->window_pointer, \
		game->collect.ptr, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
	}
	else
		mlx_put_image_to_window(game->mlx_pointer, game->window_pointer, \
		game->floor.ptr, (x * SPRITE_SIZE), (y * SPRITE_SIZE));
}

static void	map_check_one(t_game *game, int y, int x)
{
	if (!is_surrounded_by_trees(game))
		endgame("Not surrounded by trees!", game, map_char_error);
	else if (!are_collectibles_reachable(game))
		endgame("Not all collectibles are reachable!", game, map_char_error);
	else if (!is_valid_character(game, y, x))
		endgame("Invalid character in map", game, map_char_error);
	else
		check_map_maker(game, y, x);
}

void	render_map(t_game *game)
{
	t_point	coord;

	if (game->plot.map == NULL)
		endgame("Invalid map: NULL", game, error);
	coord.y = 0;
	while (coord.y < game->plot.height)
	{
		coord.x = 0;
		while (coord.x < game->plot.length)
		{
			map_check_one(game, coord.y, coord.x);
			coord.x++;
		}
		coord.y++;
	}
}
