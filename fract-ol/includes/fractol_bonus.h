/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:17:01 by adiler            #+#    #+#             */
/*   Updated: 2024/09/04 19:05:46 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "printf/ft_printf.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

# define SIZE 1000

# define ESC 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define R 114
# define C 99

# define SCROLL_UP 4
# define SCROLL_DOWN 5

typedef struct s_fractal
{
	void	*mlx;
	void	*window;
	void	*image;
	void	*pointer_to_image;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x;
	int		y;
	double	zx;
	double	zy;
	double	cx;
	double	cy;
	int		color;
	double	offset_x;
	double	offset_y;
	double	zoom;
	char	*name;
	int		max_iterations;
	char    **argv;
    int     argc;
}			t_fractal;

void	init_fractal(t_fractal *fractal);
void	init_mlx(t_fractal *fractal);
int		exit_fractal(t_fractal *fractal);
void	put_color_to_pixel(t_fractal *fractal, int x, int y, int color);
void	zoom(t_fractal *fractal, int x, int y, int zoom);
double	ft_atof(const char *str);
void	print_usage(void);
void	draw_fractal(t_fractal *fractal);
int		key_hook(int key_code, t_fractal *fractal);
int		mouse_hook(int mouse_code, int x, int y, t_fractal *fractal);
double	ft_atof(const char *str);
void	parse_arguments(t_fractal *fractal, int argc, char ** argv);

#endif