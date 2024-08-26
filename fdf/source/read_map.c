#include "../includes/fdf.h"

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

static void	fill_points(char *line, t_point *points, t_map *map)
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
		if (points[x].z < map->min_z)
			map->min_z = points[x].z;
		if (points[x].z > map->max_z)
			map->max_z = points[x].z;
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
	map->min_z = INT_MAX;
	map->max_z = INT_MIN;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_points(line, map->points[y], map);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	close(fd);
}
