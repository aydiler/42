/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:16:54 by adiler            #+#    #+#             */
/*   Updated: 2024/09/04 19:17:50 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	init_fractal(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	fractal->color = 0xFCBE11;
	fractal->zoom = 300;
	fractal->offset_x = -1.21;
	fractal->offset_y = -1.21;
	fractal->max_iterations = 42;
}

void	init_mlx(t_fractal *fractal)
{
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, SIZE, SIZE, "Fract-ol");
	fractal->image = mlx_new_image(fractal->mlx, SIZE, SIZE);
	fractal->pointer_to_image = mlx_get_data_addr(fractal->image,
			&fractal->bits_per_pixel,
			&fractal->size_line,
			&fractal->endian);
}

int	exit_fractal(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->image);
	mlx_destroy_window(fractal->mlx, fractal->window);
	mlx_destroy_display(fractal->mlx);
	free(fractal->mlx);
	exit(1);
	return (0);
}

void	put_color_to_pixel(t_fractal *fractal, int x, int y, int color)
{
	int	*buffer;

	buffer = fractal->pointer_to_image;
	buffer[(y * fractal->size_line / 4) + x] = color;
}

void draw_fractal(t_fractal *fractal)
{
    if (ft_strncmp(fractal->name, "mandelbrot", 10) == 0)
    {
        draw_mandelbrot(fractal);
    }
    else if (ft_strncmp(fractal->name, "julia", 5) == 0)
    {
        draw_julia(fractal);
    }
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);

}

double ft_atof(const char *str)
{
	double result = 0.0;
	double factor = 1.0;
	int sign = 1;
	int decimal_seen = 0;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
		{
			if (decimal_seen)
			{
				factor *= 0.1;
				result += (*str - '0') * factor;
			}
			else
				result = result * 10.0 + (*str - '0');
		}
		else if (*str == '.' && !decimal_seen)
			decimal_seen = 1;
		else
			return 0.0;
		str++;
	}
	return sign * result;
}
