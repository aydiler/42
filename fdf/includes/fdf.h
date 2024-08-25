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

typedef struct s_map
{
	void	*mlx_pointer;
	void	*window_pointer;
	int		width;
	int		height;
	t_point	**points;
	int		min_z;
	int		max_z;
}	t_map;

void	init_window(t_map *map);

#endif