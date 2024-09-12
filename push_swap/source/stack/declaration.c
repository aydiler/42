/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declaration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:07:59 by adiler            #+#    #+#             */
/*   Updated: 2024/09/12 19:08:02 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_list	**stack_a(void)
{
	static t_list	*stack;

	return (&stack);
}

t_list	**stack_b(void)
{
	static t_list	*stack;

	return (&stack);
}
