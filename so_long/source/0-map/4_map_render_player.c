/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_map_render_player.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 03:06:24 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/05/21 17:40:46 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	render_player(t_game *game);

void	player_init(t_game	*game)
{
	t_point	point;

	point.y = 0;
	while (game->plot.map[point.y])
	{
		point.x = 0;
		while (game->plot.map[point.y][point.x])
		{
			if (game->plot.map[point.y][point.x] == 'P')
			{
				game->character.x = (SPRITE_SIZE * point.x);
				game->character.y = (SPRITE_SIZE * point.y);
				render_player(game);
				return ;
			}
			point.x++;
		}
		point.y++;
	}
	return ;
}

static void	render_player(t_game *game)
{
	mlx_put_image_to_window(game->mlx_pointer, game->window_pointer,
		game->character.ptr, game->character.x, game->character.y);
}
