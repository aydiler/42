/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 14:46:36 by adiler            #+#    #+#             */
/*   Updated: 2023/12/13 17:02:30 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	intlen(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = -n;
		count++;
	}
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static unsigned int	intlen_u(unsigned int n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		count++;
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

void	ft_print_d(va_list args, int *count, char format)
{
	int				number;
	unsigned int	unsigned_number;

	number = 0;
	unsigned_number = 0;
	if (format == 'i' || format == 'd')
	{
		number = va_arg(args, int);
		ft_putnbr_fd(number, 1);
		*count += intlen(number);
	}
	if (format == 'u')
	{
		unsigned_number = (unsigned int)va_arg(args, int);
		ft_putnbr_fd_u(unsigned_number, 1);
		*count += intlen_u(unsigned_number);
	}
}
