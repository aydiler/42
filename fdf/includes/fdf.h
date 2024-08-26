#ifndef FDF_H
# define FDF_H

# include "./libft/libft.h"
# include "./minilibx-linux/mlx.h"
# include "./get_next_line/get_next_line_bonus.h"
# include "./printf/ft_printf.h"

# include <fcntl.h>//open, O_RDONLY
# include <unistd.h>//read, close, write
# include <stdlib.h>//malloc
# include <stdio.h>//printf
# include <stdbool.h>//bool
# include <limits.h>
# include <math.h>

# define ESC 65307
# define ENDC "\033[0m"
# define WINDOW_NAME "FDF"
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

typedef struct s_point
{
	int		z;
	double	iso_x;
	double	iso_y;
}	t_point;

typedef struct s_line
{
	double	dx;
	double	dy;
	int		steps;
	double	z_diff;
}	t_line;

typedef struct s_map
{
	void	*mlx_pointer;
	void	*window_pointer;
	int		width;
	int		height;
	t_point	**points;
	int		min_z;
	int		max_z;
	int		offset_x;
	int		offset_y;
	float	zoom;
}	t_map;

void	init_window(t_map *map);
void	read_map(char *filename, t_map *map);
void	draw_lines(t_map *map);
void	terminate(char *message, t_map *map, int error_code);
void	cleanup(t_map *map);
void	calculate_isometric(t_map *map);

#endif