/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:27:05 by adiler            #+#    #+#             */
/*   Updated: 2023/12/22 17:36:21 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	function_caller(char c, va_list args, int *count)
{
	if (c == 'c')
	{
		ft_putchar_fd(va_arg(args, int), 1);
		(*count)++;
	}
	if (c == 's')
		ft_print_s(args, count);
	if (c == 'p')
		ft_print_p(args, count);
	if (c == 'd' || c == 'i' || c == 'u')
		ft_print_d(args, count, c);
	if (c == 'x' || c == 'X')
		ft_print_x(args, count, c);
	if (c == '%')
	{
		ft_putchar_fd('%', 1);
		(*count)++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, str);
	while (*str)
	{
		if (*str == '%')
		{
			function_caller(*(++str), args, &count);
			str++;
		}
		else
		{
			ft_putchar_fd(*str++, 1);
			count++;
		}
	}
	va_end(args);
	return (count);
}

// int main()
// {
// // 	int test = 10;
// 	int count;
// 	int count2;
// // 	printf("chatacter test: \n");
// // 	count = ft_printf("t: %c", 'X');
// // 	count2 = printf("\nt: %c", 'X') - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("string test: \n");
// // 	count = ft_printf("t: %s", "test");
// // 	count2 = printf("\nt: %s", "test") - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// 	printf("string test: \n");
// 	count = ft_printf("t: %s", "");
// 	count2 = printf("\nt: %s", "") - 1;
// 	printf("\nft_printf count: %i", count);
// 	printf("\nprintf count: %i\n", count2);
// // 	printf("pointer test: \n");
// // 	count = ft_printf("t: %p", &test);
// // 	count2 = printf("\nt: %p", &test) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("pointer test: \n");
// // 	count = ft_printf("t: %p", NULL);
// // 	count2 = printf("\nt: %p", NULL) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("decimal test: \n");
// // 	count = ft_printf("t: %i", 44);
// // 	count2 = printf("\nt: %i", 44) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("decimal test: \n");
// // 	count = ft_printf("t: %i", -44);
// // 	count2 = printf("\nt: %i", -44) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("decimal test: \n");
// // 	count = ft_printf("t: %i", 0x44);
// // 	count2 = printf("\nt: %i", 0x44) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("unsigned test: \n");
// // 	count = ft_printf("t: %u", 123);
// // 	count2 = printf("\nt: %u", 123) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("unsigned test: \n");
// // 	count = ft_printf("t: %u", -123);
// // 	count2 = printf("\nt: %u", -123) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("hexadecimal test: \n");
// // 	count = ft_printf("t: %x", 123);
// // 	count2 = printf("\nt: %x", 123) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("hexadecimal test: \n");
// // 	count = ft_printf("t: %x", -1);
// // 	count2 = printf("\nt: %x", -1) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("hexadecimal test: \n");
// // 	count = ft_printf("t: %x", -2147483647);
// // 	count2 = printf("\nt: %x", -2147483647) - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// // 	printf("percent test: \n");
// // 	count = ft_printf("t: %%");
// // 	count2 = printf("\nt: %%") - 1;
// // 	printf("\nft_printf count: %i", count);
// // 	printf("\nprintf count: %i\n", count2);
// }
