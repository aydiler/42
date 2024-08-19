/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:28:10 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/19 20:09:33 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	init_game(t_game *game, char *path);
static bool	is_ber_file(const char *argv);
static void	init_hook(t_game *game, int event, \
int mask, int (*f)());

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc == 2 && !(is_ber_file(argv[1])))
		endgame("Can't open file. The format is not supported!", &game, error);
	else if (argc > 2)
		endgame("Can't open multiple files!", &game, error);
	else if (argc == 2 && (is_ber_file(argv[1])))
		init_game(&game, argv[1]);
	endgame("Please specify file name!", &game, error);
	return (0);
}

static void init_game(t_game *game, char *path)
{
    printf("Debug: Entering init_game\n");

    printf("Debug: About to call init_map\n");
    init_map(game, path);
    printf("Debug: After init_map\n");

    printf("Debug: game->plot.map=%p, game->plot.height=%d, game->plot.length=%d\n", 
           (void*)game->plot.map, game->plot.height, game->plot.length);

    // Print the first few lines of the map to verify its content
    for (int i = 0; i < game->plot.height && i < 5; i++) {
        printf("Debug: Map line %d: %s\n", i, game->plot.map[i]);
    }

    printf("Debug: About to call init_window\n");
    init_window(game);
    printf("Debug: After init_window\n");

    printf("Debug: About to call init_images\n");
    init_images(game);
    printf("Debug: After init_images\n");

    printf("Debug: About to call render_map\n");
    render_map(game);
    printf("Debug: After render_map\n");

    printf("Debug: About to initialize hooks\n");
    init_hook(game, KEY_RELEASE, KEY_RELEASE_MASK, key_check);
    init_hook(game, DESTROY_NOTIFY, NO_EVENT_MASK, red_cross);
    init_hook(game, EXPOSE, EXPOSURE_MASK, mini_maker);
    printf("Debug: After initializing hooks\n");

    printf("Debug: About to enter mlx_loop\n");
    mlx_loop(game->mlx_pointer);
    printf("Debug: After mlx_loop (this line should not be reached)\n");
}


static bool	is_ber_file(const char *argv)
{
	char	*string;

	string = ft_strrchr(argv, '.');
	if (string)
		return (ft_strncmp(string, ".ber", 4) == 0);
	return (false);
}

static void	init_hook(t_game *game, int event, int mask, int (*f)())
{
	mlx_hook(
		game->window_pointer,
		event,
		mask,
		f,
		game);
}
