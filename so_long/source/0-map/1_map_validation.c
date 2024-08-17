/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_map_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:12:23 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/05/21 20:58:13 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

bool is_surrounded_by_trees(t_game *game)
{
    // Check first and last row
    for (int x = 0; x < game->plot.length - 1; x++)
    {
        if (game->plot.map[0][x] != '1' || game->plot.map[game->plot.height - 1][x] != '1')
        {
            printf("Error: Not surrounded by trees!\n");
            return false;
        }
    }

    // Check first and last column
    for (int y = 0; y < game->plot.height; y++)
    {
        if (game->plot.map[y][0] != '1' || game->plot.map[y][game->plot.length - 2] != '1')
        {
            printf("Error: Not surrounded by trees!\n");
            return false;
        }
    }

    return true;
}

bool	is_rectangular(t_game *game)
{
	if (game->plot.height == game->plot.length)
	{
		return (false);
	}
	return (true);
}

bool is_valid_character(t_game *game, int y, int x)
{
    char c = game->plot.map[y][x];

    if (c == '\n')
    {
        return true;
    }

    if (!(ft_strchr("01CEP", c)))
    {
        printf("Invalid character: '%c' at position: y=%d, x=%d\n", c, y, x);
        return false;
    }

    return true;
}

bool	is_double_line(char *string_map, int i)
{
    // Check if i + 1 is within bounds before accessing string_map[i + 1]
    if ((size_t)(i + 1) < ft_strlen(string_map))
    {
        return ((string_map[i] == '\n') && (ft_strchr("\n\0", string_map[i + 1])));
    }
    return false;
}

void	is_elements_number_valid(t_game *game, t_counter *cnt, char *temp)
{
	if (\
	!(cnt->collectible > 0 && cnt->exit == 1 && \
	cnt->start == 1 && cnt->empty > 0))
	{
		free(temp);
		endgame("elements number not valid", game, file_error);
	}
}
