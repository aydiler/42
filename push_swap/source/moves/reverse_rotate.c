/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:05:59 by adiler            #+#    #+#             */
/*   Updated: 2024/09/12 19:06:06 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"

/* Top goes to bottom, anti-clockwise */
static void	ft_reverse_rotate(t_list **head)
{
	t_list	*current;
	t_list	*penultimo;
	t_list	*last;

	if (!head || !*head || !(*head)->next)
		return ;
	current = *head;
	last = ft_lstlast(*head);
	penultimo = *head;
	while (penultimo->next != last)
		penultimo = penultimo->next;
	*head = last;
	last->next = current;
	penultimo->next = NULL;
}

void	ft_rra(void)
{
	ft_reverse_rotate(stack_a());
	write(1, "rra\n", 4);
}

void	ft_rrb(void)
{
	ft_reverse_rotate(stack_b());
	write(1, "rrb\n", 4);
}

void	ft_rrr(void)
{
	ft_reverse_rotate(stack_a());
	ft_reverse_rotate(stack_b());
	write(1, "rrr\n", 4);
}
