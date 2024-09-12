/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:05:30 by adiler            #+#    #+#             */
/*   Updated: 2024/09/12 19:05:31 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

static int	ft_push_element(t_list **head, t_list **target)
{
	t_list	*current;
	t_list	*temporary;

	if (!head || !*head)
		return (1);
	current = *head;
	(*head) = (*head)->next;
	if (!*target)
	{
		(*target) = current;
		(*target)->next = NULL;
		return (0);
	}
	temporary = (*target);
	(*target) = current;
	(*target)->next = temporary;
	return (0);
}

void	ft_pa(void)
{
	t_list	**a;
	t_list	**b;

	a = stack_a();
	b = stack_b();
	if (a && b && *b)
	{
		ft_push_element(b, a);
		write(1, "pa\n", 3);
	}
}

void	ft_pb(void)
{
	t_list	**a;
	t_list	**b;

	a = stack_a();
	b = stack_b();
	if (a && b && *a)
	{
		ft_push_element(a, b);
		write(1, "pb\n", 3);
	}
}
