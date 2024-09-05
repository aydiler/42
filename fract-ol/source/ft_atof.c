/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:16:35 by adiler            #+#    #+#             */
/*   Updated: 2024/09/04 19:19:33 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static double	parse_digits(const char *str, int *decimal_seen)
{
	double	result;
	double	factor;

	result = 0.0;
	factor = 1.0;
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
			return (0.0);
		str++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		sign;
	int		decimal_seen;

	sign = 1;
	decimal_seen = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (sign * parse_digits(str, &decimal_seen));
}