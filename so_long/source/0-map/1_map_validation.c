/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_map_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:12:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/08/19 20:34:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool	is_surrounded_by_trees(t_game *game)
{
	int	i;

	if (game->plot.map == NULL)
		return (false);
	if (game->plot.height < 2 || game->plot.length < 2)
		return (false);
	i = 0;
	while (i < game->plot.length - 1)
	{
		if (game->plot.map[0] == NULL || \
			game->plot.map[game->plot.height - 1] == NULL)
			return (false);
		if (i < game->plot.height && (game->plot.map[i] == NULL || \
			game->plot.map[i][0] == '\0' || \
			game->plot.map[i][game->plot.length - 2] == '\0'))
			return (false);
		if (game->plot.map[0][i] != '1' ||
			game->plot.map[game->plot.height - 1][i] != '1' ||
			(i < game->plot.height && (game->plot.map[i][0] != '1' ||
			game->plot.map[i][game->plot.length - 2] != '1')))
			return (false);
		i++;
	}
	return (true);
}

bool	is_rectangular(t_game *game)
{
	if (game->plot.height == game->plot.length)
		return (false);
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
