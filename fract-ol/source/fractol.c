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

int	key_hook(int key_code, t_fractal *fractal)
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
	// else if (key_code == J)
	// 	set_random_julia(&fractal->cx, &fractal->cx);
	// else if (key_code == M || key_code == P)
	// 	change_iterations(fractal, key_code);
	// draw_fractal(fractal, fractal->name);
	return (0);
}

// int	mouse_hook(int mouse_code, int x, int y, t_fractal *fractal)
// {
// 	if (mouse_code == SCROLL_UP)
// 		zoom(fractal, x, y, 1);
// 	else if (mouse_code == SCROLL_DOWN)
// 		zoom(fractal, x, y, -1);
// 	draw_fractal(fractal, fractal->name);
// 	return (0);
// }

int	main()
{
	t_fractal	fractal;

	// if (argc != 2)
	// {
	// 	ft_putendl_fd("Usage: ./fractol <fractal>", 1);
	// 	ft_putendl_fd("Available fractals: mandelbrot, julia, burningship", 1);
	// 	return (0);
	// }
	// fractal = malloc(sizeof(t_fractal));
	init_fractal(&fractal);
	init_mlx(&fractal);
	mlx_key_hook((&fractal)->window, key_hook, &fractal);
	// mlx_mouse_hook(fractal->window, mouse_hook, fractal);
	mlx_hook((&fractal)->window, 17, 0L, exit_fractal, &fractal);
	// draw_fractal(fractal, argv[1]);
	mlx_loop((&fractal)->mlx);
	return (0);
}
