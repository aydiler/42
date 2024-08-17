/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 19:27:54 by adiler            #+#    #+#             */
/*   Updated: 2023/12/13 17:04:40 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include "libft/libft.h"

int		ft_printf(const char *str, ...);
void	ft_print_s(va_list args, int *count);
void	ft_print_p(va_list args, int *count);
void	ft_print_d(va_list args, int *count, char format);
void	ft_print_x(va_list args, int *count, char format);

#endif