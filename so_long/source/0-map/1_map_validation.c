/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_map_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:12:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/08/20 00:25:19 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool	is_surrounded_by_trees(t_game *game)
{
	int	x;
	int	y;

	if (game->plot.map == NULL || \
		game->plot.height < 3 || \
		game->plot.length < 3)
		return (false);
	y = 0;
	while (y < game->plot.height)
	{
		x = 0;
		while (x < game->plot.length)
		{
			if ((y == 0 || y == game->plot.height - 1 || \
					x == 0 || x == game->plot.length - 1) && \
				game->plot.map[y][x] != '1')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	is_valid_character(t_game *game, int y, int x)
{
	char	c;

	c = game->plot.map[y][x];
	if (c == '\n')
		return (true);
	if (!(ft_strchr("01CEP", c)))
		return (false);
	return (true);
}

bool	is_double_line(char *string_map, int i)
{
	if ((size_t)(i + 1) < ft_strlen(string_map))
		return ((string_map[i] == '\n') && \
			(ft_strchr("\n\0", string_map[i + 1])));
	return (false);
}

void	is_elements_number_valid(t_game *game, t_counter *cnt, char *temp)
{
	if (!(cnt->collectible > 0 && cnt->exit == 1 && \
		cnt->start == 1 && cnt->empty > 0))
	{
		free(temp);
		endgame("elements number not valid", game, file_error);
	}
}
