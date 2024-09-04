/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:16:35 by adiler            #+#    #+#             */
/*   Updated: 2024/09/04 19:19:33 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

/*
Mandelbrot set algebraically:
z = z^2 + c
 = (a+bi)^2 + (c+di)
 = a^2 + 2abi - b^2 + c + di
 = a^2 - b^2 + c + (2ab + d)i
 = z_real + z_imaginary
z_real = a^2 - b^2 + c
z_imaginary = (2ab + d)i

Mandelbrot set geometrically:
z_real: zx = zx^2 - zy^2 + cx
z_imaginary: zy = 2 * zx * zy + cy

Escape condition algebraically:
|z| < 2
sqrt(a^2 + b^2) < 2
a^2 + b^2 < 4

Escape condition geometrically:
zx^2 + zy^2 < 4
*/

void	calculate_mandelbrot(t_fractal *fractal)
{
	int		i;
	double	x_temp;

	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
	while (++i < fractal->max_iterations)
	{
		x_temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2 * fractal->zx * fractal->zy + fractal->cy;
		fractal->zx = x_temp;
		if (fractal->zx * fractal->zx + fractal->zy
			* fractal->zy >= __DBL_MAX__)
			break ;
	}
	if (i == fractal->max_iterations)
		put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color * (i
					% 255)));
}

void	calculate_julia(t_fractal *fractal)
{
	int		i;
	double	tmp;

	fractal->zx = fractal->x / fractal->zoom + fractal->offset_x;
	fractal->zy = fractal->y / fractal->zoom + fractal->offset_y;
	i = 0;
	while (++i < fractal->max_iterations)
	{
		tmp = fractal->zx;
		fractal->zx = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = 2 * fractal->zy * tmp + fractal->cy;
		if (fractal->zx * fractal->zx + fractal->zy
			* fractal->zy >= __DBL_MAX__)
			break ;
	}
	if (i == fractal->max_iterations)
		put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color * (i
					% 255)));
}

void	calculate_burning_ship(t_fractal *fractal)
{
	int		i;
	double	x_temp;

	fractal->name = "ship";
	i = 0;
	fractal->zx = 0.0;
	fractal->zy = 0.0;
	fractal->cx = (fractal->x / fractal->zoom) + fractal->offset_x;
	fractal->cy = (fractal->y / fractal->zoom) + fractal->offset_y;
	while (++i < fractal->max_iterations)
	{
		x_temp = fractal->zx * fractal->zx - fractal->zy * fractal->zy
			+ fractal->cx;
		fractal->zy = fabs(2.0 * fractal->zx * fractal->zy) + fractal->cy;
		fractal->zx = fabs(x_temp);
		if (fractal->zx * fractal->zx + fractal->zy
			* fractal->zy >= __DBL_MAX__)
			break ;
	}
	if (i == fractal->max_iterations)
		put_color_to_pixel(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_color_to_pixel(fractal, fractal->x, fractal->y, (fractal->color
				* i));
}

void	draw_fractal(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZE)
	{
		while (fractal->y < SIZE)
		{
			if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
				calculate_mandelbrot(fractal);
			else if (ft_strncmp(fractal->name, "julia", 5) == 0)
				calculate_julia(fractal);
			else if (ft_strncmp(fractal->name, "burningship", 11) == 0)
				calculate_burning_ship(fractal);
			fractal->y++;
		}
		fractal->x++;
		fractal->y = 0;
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc < 2)
	{
		print_usage();
		return (0);
	}
	init_fractal(&fractal);
	fractal.argc = argc;
	fractal.argv = argv;
	parse_arguments(&fractal, argc, argv);
	init_mlx(&fractal);
	draw_fractal(&fractal);
	mlx_key_hook((&fractal)->window, key_hook, (&fractal));
	mlx_mouse_hook((&fractal)->window, mouse_hook, (&fractal));
	mlx_hook((&fractal)->window, 17, 0L, exit_fractal, (&fractal));
	mlx_loop((&fractal)->mlx);
	return (0);
}
