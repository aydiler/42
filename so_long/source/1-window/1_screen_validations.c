/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_screen_validations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:12:37 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/05/21 17:41:24 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_point	get_screen_size(t_game *game)
{
	t_point	point;

	mlx_get_screen_size(game->mlx_pointer, &point.x, &point.y);
	return (point);
}

bool	is_larger_than_window(t_game *game)
{
	t_point	screen_size;

	screen_size = get_screen_size(game);
	return (\
	((game->plot.length * SPRITE_SIZE) > screen_size.x) \
	|| \
	((game->plot.height * SPRITE_SIZE) > screen_size.y) \
	);
}
