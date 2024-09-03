#include "../includes/fdf.h"

int main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}

	map.mlx_pointer = NULL;
	map.window_pointer = NULL;
	map.width = 0;
	map.height = 0;
	map.points = NULL;

	init_window(&map);
	read_map(argv[1], &map);
	calculate_isometric(&map);
	draw_lines(&map);
	mlx_loop(map.mlx_pointer);
	return (0);
}

void	free_map_points(t_map *map)
{
	int	i;

	if (map->points)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->points[i]);
			i++;
		}
		free(map->points);
		map->points = NULL;
	}
}

void	cleanup(t_map *map)
{
	free_map_points(map);
	if (map->window_pointer)
		mlx_destroy_window(map->mlx_pointer, map->window_pointer);
	if (map->mlx_pointer)
	{
		mlx_destroy_display(map->mlx_pointer);
		free(map->mlx_pointer);
	}
}

void	terminate(char *message, t_map *map, int error_code)
{
	ft_printf("Error\n%s\n", message);
	cleanup(map);
	exit(error_code);
}

void	calculate_isometric(t_map *map)
{
	int		x;
	int		y;
	double	angle;
	double	z_scale;

	angle = 0.40;
	z_scale = 0.1;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->points[y][x].iso_x = (x - y) * cos(angle);
			map->points[y][x].iso_y = -map->points[y][x].z * \
				z_scale + (x + y) * sin(angle);
			x++;
		}
		y++;
	}
}

/*
void	print_map(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("(%.2f,%.2f,%d) ", map->points[y][x].iso_x,
				map->points[y][x].iso_y, map->points[y][x].z);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}
*/