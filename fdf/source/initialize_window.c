#include "../includes/fdf.h"

int	resize_window(t_map *map);
int	close_window(t_map *map);
int	key_hook(int keycode, t_map *map);

void	init_window(t_map *map)
{
	map->mlx_pointer = mlx_init();
	if (!map->mlx_pointer)
		terminate("Failed to initialize MLX", map, 1);

	map->window_pointer = mlx_new_window(map->mlx_pointer, \
		WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (!map->window_pointer)
		terminate("Failed to create window", map, 1);

	mlx_key_hook(map->window_pointer, key_hook, map);
	mlx_hook(map->window_pointer, 17, 1L << 17, close_window, map);
	mlx_hook(map->window_pointer, 25, 1L << 18, resize_window, map);
}

int	resize_window(t_map *map)
{
	draw_lines(map);
	return (0);
}

int	close_window(t_map *map)
{
	cleanup(map);
	exit(0);
}

int	key_hook(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		cleanup(map);
		exit(0);
	}
	return (0);
}
