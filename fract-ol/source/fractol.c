#include "../includes/fractol.h"

void	init_fractal(t_fractal *fractal)
{
	fractal->x = 0;
	fractal->y = 0;
	fractal->cx = 0.0;
    fractal->cy = 0.0;
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

void	calculate_mandelbrot(t_fractal *fractal)
{
	int		i;
	double	x_temp;

	fractal->name = "mandelbrot";
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

	fractal->name = "julia";
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

int draw_fractal(t_fractal *fractal, char *query)
{
    if (ft_strncmp(query, "mandelbrot", 11) == 0)
    {
        draw_mandelbrot(fractal);
    }
    else if (ft_strncmp(query, "julia", 6) == 0)
    {
        if (!fractal->cx && !fractal->cy)
        {
            fractal->cx = -0.745429;
            fractal->cy = 0.05;
        }
        draw_julia(fractal);
    }
    else
        exit_fractal(fractal);
    mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0, 0);
    return (0);
}

int	key_hook(int key_code, t_fractal *fractal)
{
	ft_printf("key code: %d\n", key_code);
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
	draw_fractal(fractal, fractal->name);
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

int	mouse_hook(int mouse_code, int x, int y, t_fractal *fractal)
{
	ft_putstr_fd("Mouse event: ", 2);
	ft_putnbr_fd(mouse_code, 2);
	ft_putchar_fd('\n', 2);
	if (mouse_code == SCROLL_UP)
	{
		zoom(fractal, x, y, 1);
		draw_fractal(fractal, fractal->name);
	}
	else if (mouse_code == SCROLL_DOWN)
	{
		zoom(fractal, x, y, -1);
		draw_fractal(fractal, fractal->name);
	}
	return (0);
}

int	resize_window(t_fractal *fractal)
{
	draw_fractal(fractal, fractal->name);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./fractol <fractal>", 1);
		ft_putendl_fd("Available fractals: mandelbrot, julia, burningship", 1);
		return (0);
	}
	init_fractal(&fractal);
	init_mlx(&fractal);
	mlx_key_hook((&fractal)->window, key_hook, &fractal);
	mlx_mouse_hook((&fractal)->window, mouse_hook, &fractal);
	mlx_hook((&fractal)->window, 17, 0L, exit_fractal, &fractal);
	mlx_hook((&fractal)->window, 25, 1L << 18, resize_window, &fractal);
	draw_fractal(&fractal, argv[1]);
	mlx_loop((&fractal)->mlx);
	return (0);
}
