/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:28:10 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/20 17:31:33 by ubuntu           ###   ########.fr       */
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

static void	init_game(t_game *game, char *path)
{
	init_map(game, path);
	init_window(game);
	init_images(game);
	render_map(game);
	init_hook(game, KEY_RELEASE, KEY_RELEASE_MASK, key_check);
	init_hook(game, DESTROY_NOTIFY, NO_EVENT_MASK, red_cross);
	init_hook(game, EXPOSE, EXPOSURE_MASK, mini_maker);
	mlx_loop(game->mlx_pointer);
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
