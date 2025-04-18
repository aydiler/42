/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declaration.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:07:59 by adiler            #+#    #+#             */
/*   Updated: 2024/09/14 18:54:31 by adiler           ###   ########.fr       */
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

int	add_to_stack(t_list **stack, int number)
{
	t_list	*new_node;

	new_node = ft_lstnew((void *)(intptr_t)number);
	if (!new_node)
		return (0);
	ft_lstadd_back(stack, new_node);
	return (1);
}

int	is_valid_int_string(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
