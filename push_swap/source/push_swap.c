/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:08:28 by adiler            #+#    #+#             */
/*   Updated: 2024/09/14 20:17:09 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static int	get_max_bits(t_list *stack)
{
	t_list	*current;
	long	max;
	int		max_bits;

	current = stack;
	max = 0;
	while (current)
	{
		if ((intptr_t)current->content > max)
			max = (intptr_t)current->content;
		current = current->next;
	}
	max_bits = 0;
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

static void	radix_sort_bit(t_list **a, t_list **b, int bit)
{
	int		size;
	int		i;
	long	num;

	size = ft_lstsize(*a);
	i = 0;
	while (i++ < size)
	{
		num = (intptr_t)(*a)->content;
		if (((num >> bit) & 1) == 1)
		{
			ft_ra();
			// print_stacks(*a, *b);
		}
		else
		{
			ft_pb();
			// print_stacks(*a, *b);
		}
	}
	while (*b)
		ft_pa();
	// print_stacks(*a, *b);
}

void	radix_sort(t_list **a, t_list **b)
{
	int	max_bits;
	int	i;

	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		radix_sort_bit(a, b, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_list	**a;
	t_list	**b;

	if (argc < 2)
		return (1);
	a = stack_a();
	b = stack_b();
	if (!process_arguments(argc, argv))
		return (1);
	radix_sort(a, b);
	free_stack(a);
	free_stack(b);
	return (0);
}
