/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:16:46 by adiler            #+#    #+#             */
/*   Updated: 2024/09/04 19:10:14 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol_bonus.h"

int key_hook(int key_code, t_fractal *fractal)
{
    if (key_code == ESC)
        exit_fractal(fractal);
    else if (key_code == LEFT)
        fractal->offset_x -= 42 / fractal->zoom;
    else if (key_code == RIGHT)
        fractal->offset_x += 42 / fractal->zoom;
    else if (key_code == UP)
        fractal->offset_y -= 42 / fractal->zoom;
    else if (key_code == DOWN)
        fractal->offset_y += 42 / fractal->zoom;
    else if (key_code == R)
        init_fractal(fractal);
    else if (key_code == C)
        fractal->color += (255 * 255 * 255) / 100;
    draw_fractal(fractal);
    return (0);
}

void	zoom(t_fractal *fractal, int x, int y, int zoom)
{
	double	zoom_level;

	zoom_level = 1.42;
	if (zoom == 1)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x)
			- (x / (fractal->zoom * zoom_level));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y)
			- (y / (fractal->zoom * zoom_level));
		fractal->zoom *= zoom_level;
	}
	else if (zoom == -1)
	{
		fractal->offset_x = (x / fractal->zoom + fractal->offset_x)
			- (x / (fractal->zoom / zoom_level));
		fractal->offset_y = (y / fractal->zoom + fractal->offset_y)
			- (y / (fractal->zoom / zoom_level));
		fractal->zoom /= zoom_level;
	}
}

int mouse_hook(int mouse_code, int x, int y, t_fractal *fractal)
{
    if (mouse_code == SCROLL_UP)
    {
        zoom(fractal, x, y, 1);
        draw_fractal(fractal);
    }
    else if (mouse_code == SCROLL_DOWN)
    {
        zoom(fractal, x, y, -1);
        draw_fractal(fractal);
    }
    return (0);
}