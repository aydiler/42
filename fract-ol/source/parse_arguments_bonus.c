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

#include "../includes/fractol_bonus.h"

static void	handle_mandelbrot(t_fractal *fractal, int argc)
{
	if (argc != 2)
	{
		ft_putendl_fd("Mandelbrot doesn't require additional parameters", 1);
		print_usage();
		exit(0);
	}
	fractal->name = "mandelbrot";
}

static void	handle_julia(t_fractal *fractal, int argc, char **argv)
{
	if (argc != 4)
	{
		ft_putendl_fd("Julia requires two additional parameters", 1);
		print_usage();
		exit(0);
	}
	fractal->name = "julia";
	fractal->cx = ft_atof(argv[2]);
	fractal->cy = ft_atof(argv[3]);
}

static void	handle_burningship(t_fractal *fractal, int argc)
{
	if (argc != 2)
	{
		ft_putendl_fd("Burning Ship doesn't require additional parameters", 1);
		print_usage();
		exit(0);
	}
	fractal->name = "burningship";
}

void	parse_arguments(t_fractal *fractal, int argc, char **argv)
{
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		handle_mandelbrot(fractal, argc);
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
		handle_julia(fractal, argc, argv);
	else if (ft_strncmp(argv[1], "burningship", 12) == 0)
		handle_burningship(fractal, argc);
	else
	{
		print_usage();
		exit(0);
	}
}
