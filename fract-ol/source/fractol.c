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
|a + bi| < 2
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

void	draw_mandelbrot(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZE)
	{
		while (fractal->y < SIZE)
		{
			calculate_mandelbrot(fractal);
			fractal->y++;
		}
		fractal->x++;
		fractal->y = 0;
	}
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

void	draw_julia(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	while (fractal->x < SIZE)
	{
		while (fractal->y < SIZE)
		{
			calculate_julia(fractal);
			fractal->y++;
		}
		fractal->x++;
		fractal->y = 0;
	}
}

void	print_usage(void)
{
	ft_putendl_fd("Usage:", 1);
	ft_putendl_fd("  ./fractol mandelbrot", 1);
	ft_putendl_fd("  ./fractol julia [cx] [cy]", 1);
	ft_putendl_fd("\nPossible values for Julia set:", 1);
	ft_putendl_fd("  cx: -2.0 to 2.0", 1);
	ft_putendl_fd("  cy: -2.0 to 2.0", 1);
	ft_putendl_fd("\nExample:", 1);
	ft_putendl_fd("  ./fractol julia -0.745429 0.05", 1);
}

int main(int argc, char **argv)
{
    t_fractal fractal;

	if (argc < 2)
	{
		print_usage();
		return (0);
	}
    init_fractal(&fractal);
    fractal.argc = argc;
    fractal.argv = argv;

    if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
    {
        if (argc != 2)
        {
            ft_putendl_fd("Mandelbrot doesn't require additional parameters", 1);
            print_usage();
            return (0);
        }
        fractal.name = "mandelbrot";
    }
    else if (ft_strncmp(argv[1], "julia", 6) == 0)
    {
        if (argc != 4)
        {
            ft_putendl_fd("Julia requires two additional parameters", 1);
            print_usage();
            return (0);
        }
        fractal.name = "julia";
        fractal.cx = ft_atof(argv[2]);
        fractal.cy = ft_atof(argv[3]);
    }
    else
    {
        print_usage();
        return (0);
    }
    init_mlx(&fractal);
    draw_fractal(&fractal);
    mlx_put_image_to_window(fractal.mlx, fractal.window, fractal.image, 0, 0);
    mlx_key_hook(fractal.window, key_hook, &fractal);
    mlx_mouse_hook(fractal.window, mouse_hook, &fractal);
    mlx_hook(fractal.window, 17, 0L, exit_fractal, &fractal);
    mlx_loop(fractal.mlx);
    return (0);
}
