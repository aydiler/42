/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_map_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:28:30 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/18 00:28:31 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	line_validation(char **map, t_game *game);

int	open_file(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nInvalid file\n");
		exit(1);
	}
	return (fd);
}

t_counter	new_counter(void)
{
	t_counter	counter;

	counter.collectible = 0;
	counter.start = 0;
	counter.exit = 0;
	counter.movements = 0;
	counter.empty = 0;
	return (counter);
}

int	len_map_validation(char **map, t_game *game)
{
	line_validation(map, game);
	return (ft_strlen(map[0]));
}

static void line_validation(char **map, t_game *game)
{
    int     i;
    t_point point;

    i = 0;
    point.x = 0;
    point.y = ft_strlen(map[0]);
    while (map[i] != 0)
    {
        point.x = ft_strlen(map[i]);
        // Print out the index, the line and its length
        printf("Line %d: '%s', length: %d\n", i, map[i], point.x);
        if (point.x != point.y)
        {
            // Also print out the expected length for comparison
            printf("Error: line %d length (%d) does not match expected length (%d)\n", i, point.x, point.y);
            free_map(game);
            endgame("Invalid file: lines are not the same size!", game, error);
        }
        i++;
    }
}