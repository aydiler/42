/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_p.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:37:21 by adiler            #+#    #+#             */
/*   Updated: 2023/12/13 17:02:31 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_print_hex(unsigned long addr, int *count)
{
	if (addr >= 16)
		ft_print_hex(addr / 16, count);
	ft_putchar_fd("0123456789abcdef"[addr % 16], 1);
	(*count)++;
}

void	ft_print_p(va_list args, int *count)
{
	unsigned long	addr;

	addr = va_arg(args, unsigned long);
	if (addr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		*count += 5;
	}
	else
	{
		ft_putstr_fd("0x", 1);
		*count += 2;
		ft_print_hex(addr, count);
	}
	return ;
}

// void	ft_print_p(va_list args, int *count)
// {
// 	unsigned long	addr;
// 	addr = (unsigned long)va_arg(args, void *);
// 	addr = addr + 0;
// 	*count = *count + 0;
// 	return ;
// }