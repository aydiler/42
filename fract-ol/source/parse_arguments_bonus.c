#include "../includes/fractol_bonus.h"

double parse_digits(const char *str, int *decimal_seen)
{
    double result = 0.0;
    double factor = 1.0;

    while (*str)
    {
        if (*str >= '0' && *str <= '9')
        {
            if (*decimal_seen)
            {
                factor *= 0.1;
                result += (*str - '0') * factor;
            }
            else
                result = result * 10.0 + (*str - '0');
        }
        else if (*str == '.' && !(*decimal_seen))
            *decimal_seen = 1;
        else
            return 0.0;
        str++;
    }
    return result;
}

double ft_atof(const char *str)
{
    int sign = 1;
    int decimal_seen = 0;

    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
        str++;

    return sign * parse_digits(str, &decimal_seen);
}

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

void	parse_arguments(t_fractal *fractal, int argc, char ** argv)
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