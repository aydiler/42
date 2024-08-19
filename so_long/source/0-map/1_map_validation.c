/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_map_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:12:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/08/19 20:20:25 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool is_surrounded_by_trees(t_game *game)
{
    int i;

    printf("Debug: Entering is_surrounded_by_trees\n");
    printf("Debug: game->plot.height=%d, game->plot.length=%d\n", game->plot.height, game->plot.length);

    if (game->plot.map == NULL)
    {
        printf("Error: game->plot.map is NULL\n");
        return false;
    }

    if (game->plot.height < 2 || game->plot.length < 2)
    {
        printf("Error: Map dimensions are too small\n");
        return false;
    }

    i = 0;
    while (i < game->plot.length - 1)
    {
        printf("Debug: Checking row %d\n", i);

        if (game->plot.map[0] == NULL || game->plot.map[game->plot.height - 1] == NULL)
        {
            printf("Error: NULL row in map\n");
            return false;
        }

        if (i < game->plot.height && (game->plot.map[i] == NULL || game->plot.map[i][0] == '\0' || game->plot.map[i][game->plot.length - 2] == '\0'))
        {
            printf("Error: Invalid row %d\n", i);
            return false;
        }

        if (game->plot.map[0][i] != '1' ||
            game->plot.map[game->plot.height - 1][i] != '1' ||
            (i < game->plot.height && (game->plot.map[i][0] != '1' ||
            game->plot.map[i][game->plot.length - 2] != '1')))
        {
            printf("Error: Not surrounded by trees at position %d\n", i);
            return false;
        }
        i++;
    }

    printf("Debug: Exiting is_surrounded_by_trees\n");
    return true;
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
	{
		ft_printf("Invalid character: '%c' at position: y=%d, x=%d\n", c, y, x);
		return (false);
	}
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
