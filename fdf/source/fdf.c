#include "../includes/fdf.h"

int key_hook(int keycode, t_map *map);
int close_window(t_map *map);
void	read_map(char *filename, t_map *map);
void	print_map(t_map *map);
void	calculate_isometric(t_map *map);
void	draw_lines(t_map *map);
void	draw_line(t_map *map, t_point start, t_point end, int offset_x, int offset_y, float zoom);



int main(int argc, char *argv[])
{
	t_map map;

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
	ft_printf("width: %d, height: %d\n", map.width, map.height);
	ft_printf("Printing map before converting points to isometric\n");
	print_map(&map);
	calculate_isometric(&map);
	ft_printf("Printing map after converting points to isometric\n");
	print_map(&map);
	draw_lines(&map);
	mlx_loop(map.mlx_pointer);

	return (0);
}

void init_window(t_map *map)
{
	map->mlx_pointer = mlx_init();
	if (!map->mlx_pointer)
		terminate("Failed to initialize MLX", map, 1);

	map->window_pointer = mlx_new_window(map->mlx_pointer, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (!map->window_pointer)
		terminate("Failed to create window", map, 1);

	mlx_key_hook(map->window_pointer, key_hook, map);
	mlx_hook(map->window_pointer, 17, 1L<<17, close_window, map);
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

void cleanup(t_map *map)
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


void terminate(char *message, t_map *map, int error_code)
{
	printf(RED "Error\n%s\n" ENDC, message);
	cleanup(map);
	exit(error_code);
}

int close_window(t_map *map)
{
	cleanup(map);
	exit(0);
}

int key_hook(int keycode, t_map *map)
{
	if (keycode == ESC)
	{
		cleanup(map);
		exit(0);
	}
	return (0);
}

static int	count_width(char *line)
{
	int	width;
	int	i;

	width = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
			width++;
		i++;
	}
	return (width);
}

static int	get_dimensions(char *filename, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	map->height = 0;
	map->width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map->height == 0)
			map->width = count_width(line);
		map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map->width > 0 && map->height > 0);
}

static int	allocate_points(t_map *map)
{
	int	i;

	map->points = malloc(sizeof(t_point *) * map->height);
	if (!map->points)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->points[i] = malloc(sizeof(t_point) * map->width);
		if (!map->points[i])
		{
			while (i > 0)
			{
				i--;
				free(map->points[i]);
			}
			free(map->points);
			return (0);
		}
		i++;
	}
	return (1);
}


static void	fill_points(char *line, t_point *points)
{
	char	**split;
	int		x;

	split = ft_split(line, ' ');
	if (!split)
		return ;
	x = 0;
	while (split[x])
	{
		points[x].z = ft_atoi(split[x]);
		points[x].iso_x = 0;
		points[x].iso_y = 0;
		free(split[x]);
		x++;
	}
	free(split);
}


void	read_map(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	int		y;

	if (!get_dimensions(filename, map) || !allocate_points(map))
		terminate("Failed to initialize map", map, 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		terminate("Failed to open file", map, 1);
	y = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_points(line, map->points[y]);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
}

void	calculate_isometric(t_map *map)
{
	int		x;
	int		y;
	double	angle;
	double	z_scale;

	angle = 0.523599;  // 30 degrees in radians
	z_scale = 0.1;  // Adjust this value to change the z-axis scale
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			map->points[y][x].iso_x = (x - y) * cos(angle);
			map->points[y][x].iso_y = -map->points[y][x].z * z_scale + (x + y) * sin(angle);
			x++;
		}
		y++;
	}
}



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


void	draw_lines(t_map *map)
{
	int		x;
	int		y;
	int		offset_x;
	int		offset_y;
	float	zoom;

	zoom = 20.0;  // Adjust this value to zoom in or out
	offset_x = WINDOW_WIDTH / 2 - (int)((map->width / 2) * zoom);
	offset_y = WINDOW_HEIGHT / 2 - (int)((map->height / 2) * zoom);
	
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x < map->width - 1)
				draw_line(map, map->points[y][x], map->points[y][x + 1],
					offset_x, offset_y, zoom);
			if (y < map->height - 1)
				draw_line(map, map->points[y][x], map->points[y + 1][x],
					offset_x, offset_y, zoom);
			x++;
		}
		y++;
	}
	ft_printf("Drawing completed\n");
}


void	draw_line(t_map *map, t_point start, t_point end, int offset_x, int offset_y, float zoom)
{
	double	dx;
	double	dy;
	int		steps;
	int		i;
	int		color;

	dx = (end.iso_x - start.iso_x) * zoom;
	dy = (end.iso_y - start.iso_y) * zoom;
	steps = (int)(fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy));
	if (steps == 0)
		return ;
	dx = dx / steps;
	dy = dy / steps;
	color = 0xFFFFFF;
	i = 0;
	while (i <= steps)
	{
		mlx_pixel_put(map->mlx_pointer, map->window_pointer,
			offset_x + (int)(start.iso_x * zoom + dx * i),
			offset_y + (int)(start.iso_y * zoom + dy * i),
			color);
		i++;
	}
}
