#include "../includes/fdf.h"

void	draw_line(t_map *map, t_point start, t_point end);
void	draw_line_points(t_map *map, t_point start, t_line line);
int		get_color(double z, int min_z, int max_z);

void	draw_lines(t_map *map)
{
	int		x;
	int		y;

	map->zoom = 30.0;
	map->offset_x = WINDOW_WIDTH / 2 - (int)((map->width / 2) * map->zoom);
	map->offset_y = WINDOW_HEIGHT / 2 - (int)((map->height / 2) * map->zoom);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				draw_line(map, map->points[y][x], map->points[y][x + 1]);
			if (y < map->height - 1)
				draw_line(map, map->points[y][x], map->points[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	draw_line(t_map *map, t_point start, t_point end)
{
	t_line	line;

	line.dx = (end.iso_x - start.iso_x) * map->zoom;
	line.dy = (end.iso_y - start.iso_y) * map->zoom;
	if (fabs(line.dx) > fabs(line.dy))
		line.steps = (int)fabs(line.dx);
	else
		line.steps = (int)fabs(line.dy);
	if (line.steps == 0)
		return ;
	line.dx = line.dx / line.steps;
	line.dy = line.dy / line.steps;
	line.z_diff = end.z - start.z;
	draw_line_points(map, start, line);
}

void	draw_line_points(t_map *map, t_point start, t_line line)
{
	int		i;
	int		color;
	double	z_current;

	i = 0;
	while (i <= line.steps)
	{
		z_current = start.z + (line.z_diff * i / line.steps);
		color = get_color(z_current, map->min_z, map->max_z);
		mlx_pixel_put(map->mlx_pointer, map->window_pointer,
			map->offset_x + (int)(start.iso_x * map->zoom + line.dx * i),
			map->offset_y + (int)(start.iso_y * map->zoom + line.dy * i),
			color);
		i++;
	}
}

int	get_color(double z, int min_z, int max_z)
{
	int	color;
	int	range;

	range = max_z - min_z;
	if (z < min_z + range / 3)
		color = 0xFFFFFF;
	else if (z < min_z + 2 * range / 3)
		color = 0xFFB6C1;
	else
		color = 0xFF69B4;
	return (color);
}
