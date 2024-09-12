/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stack.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:07:44 by adiler            #+#    #+#             */
/*   Updated: 2024/09/12 19:48:50 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	add_to_stack(t_list **stack, int number)
{
	t_list	*new_node;

	new_node = ft_lstnew((void *)(intptr_t)number);
	if (!new_node)
		return (0);
	ft_lstadd_back(stack, new_node);
	return (1);
}

int	process_arguments(int argc, char **argv)
{
	int		i;
	int		number;
	t_list	**a;

	a = stack_a();
	i = 1;
	while (i < argc)
	{
		number = ft_atoi(argv[i]);
		if (!add_to_stack(a, number))
		{
			ft_printf("Error\n");
			free_stack(a);
			return (0);
		}
		i++;
	}
	return (1);
}
