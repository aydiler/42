#ifndef FDF_UTILS_H
# define FDF_UTILS_H

# include <mlx.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>

# define ESC 65307
# define RED "\033[1m\033[31m"
# define GREEN "\033[1m\033[32m"
# define ENDC "\033[0m"
# define WINDOW_NAME "FDF"
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

typedef struct s_point
{
	int		z;
	double	iso_x;
	double	iso_y;
} t_point;


typedef struct s_map
{
	void    *mlx_pointer;
	void    *window_pointer;
	int     width;
	int     height;
	t_point **points;
	int		min_z;
	int		max_z;
} t_map;


void    terminate(char *message, t_map *map, int error_code);
void    init_window(t_map *map);

#endif