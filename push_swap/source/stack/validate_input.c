/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:07:44 by adiler            #+#    #+#             */
/*   Updated: 2024/09/14 20:17:00 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/push_swap.h"
#include <limits.h>

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

int	is_duplicate(t_list **stack, int num)
{
	t_list	*current;

	current = *stack;
	while (current)
	{
		if ((intptr_t)current->content == num)
			return (1);
		current = current->next;
	}
	return (0);
}

int	validate_argument(char *arg, long *number)
{
	if (!is_valid_int_string(arg))
		return (0);
	*number = ft_atoi(arg);
	if (*number > INT_MAX || *number < INT_MIN)
		return (0);
	return (1);
}

int	add_arguments_to_stack(int argc, char **argv, t_list **a)
{
	int		i;
	long	number;

	i = 1;
	while (i < argc)
	{
		if (!validate_argument(argv[i], &number) || \
			is_duplicate(a, (int)number))
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		if (!add_to_stack(a, (int)number))
		{
			ft_putstr_fd("Error\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	process_arguments(int argc, char **argv)
{
	t_list	**a;

	a = stack_a();
	if (!add_arguments_to_stack(argc, argv, a))
	{
		free_stack(a);
		return (0);
	}
	return (1);
}
