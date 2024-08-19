/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_map.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 21:29:12 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/08/19 20:21:04 by ubuntu           ###   ########.fr       */
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

static void map_check_one(t_game *game, int y, int x)
{
    printf("Debug: Entering map_check_one for cell (%d, %d)\n", y, x);

    if (game->plot.map == NULL)
    {
        printf("Error: game->plot.map is NULL in map_check_one\n");
        endgame("Invalid map: NULL", game, map_char_error);
        return;
    }

    printf("Debug: About to call is_surrounded_by_trees\n");
    bool surrounded = is_surrounded_by_trees(game);
    printf("Debug: is_surrounded_by_trees returned %d\n", surrounded);

    if (!surrounded)
    {
        printf("Debug: Map is not surrounded by trees\n");
        endgame("Not surrounded by trees!", game, map_char_error);
    }
    else
    {
        printf("Debug: About to call is_rectangular\n");
        int rectangular = is_rectangular(game);
        printf("Debug: is_rectangular returned %d\n", rectangular);

        if (!rectangular)
        {
            printf("Debug: Map is not rectangular\n");
            endgame("Map is not rectangular!", game, map_char_error);
        }
        else
        {
            printf("Debug: About to call is_valid_character\n");
            int valid_char = is_valid_character(game, y, x);
            printf("Debug: is_valid_character returned %d\n", valid_char);

            if (!valid_char)
            {
                printf("Debug: Invalid character at (%d, %d): %c\n", y, x, game->plot.map[y][x]);
                endgame("Invalid character in map", game, map_char_error);
            }
            else
            {
                printf("Debug: About to call check_map_maker for cell (%d, %d)\n", y, x);
                check_map_maker(game, y, x);
                printf("Debug: Finished check_map_maker for cell (%d, %d)\n", y, x);
            }
        }
    }

    printf("Debug: Exiting map_check_one for cell (%d, %d)\n", y, x);
}




void render_map(t_game *game)
{
    t_point coord;

    printf("Debug: Entering render_map\n");
    printf("Debug: game->plot.map=%p, game->plot.height=%d, game->plot.length=%d\n", 
           (void*)game->plot.map, game->plot.height, game->plot.length);

    if (game->plot.map == NULL)
    {
        printf("Error: game->plot.map is NULL\n");
        endgame("Invalid map: NULL", game, error);
    }

    coord.y = 0;
    while (coord.y < game->plot.height)
    {
        printf("Debug: Processing row %d\n", coord.y);
        coord.x = 0;
        while (coord.x < game->plot.length)
        {
            printf("Debug: Processing cell (%d, %d): %c\n", coord.y, coord.x, game->plot.map[coord.y][coord.x]);
            map_check_one(game, coord.y, coord.x);
            coord.x++;
        }
        coord.y++;
    }
    printf("Debug: Exiting render_map\n");
}


