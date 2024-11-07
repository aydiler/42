void skip_input_space()
{
}
int scan_char(va_list ap)
{
	return(0);
}
int scan_int(va_list ap)
{
	return(0);
}
int scan_string(va_list ap)
{
	
	return (0);
}

int receive_input(const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(fd, ap);
		case 'd':
			return scan_int(fd, ap);
		case 's':
			skip_input_space(fd);
			return scan_string(fd, ap);
		default:
			return 1;
	}
}

int ft_scanf(const char *format ...)
{
	int i = 0;
	int result = 0;
	va_list ap;

	va_start(ap, format);

	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			if (receive_input (&(format[i]),ap) != 1)
				break;
			else
				result++;
		}
		i++;
	}
	va_end(ap);
	return (result);
}

