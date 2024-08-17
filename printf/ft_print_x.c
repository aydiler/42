/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:20:23 by adiler            #+#    #+#             */
/*   Updated: 2023/12/13 17:02:35 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_hex_u(unsigned int n, int *count, char format)
{
	if (n >= 16)
	{
		ft_print_hex_u(n / 16, count, format);
	}
	if (format == 'x')
		ft_putchar_fd("0123456789abcdef"[n % 16], 1);
	else if (format == 'X')
		ft_putchar_fd("0123456789ABCDEF"[n % 16], 1);
	(*count)++;
}

void	ft_print_x(va_list args, int *count, char format)
{
	unsigned int	number;

	number = va_arg(args, unsigned int);
	ft_print_hex_u(number, count, format);
}
