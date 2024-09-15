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

int	add_number_to_stack(t_list **a, char *arg)
{
	long	number;

	if (!validate_argument(arg, &number) || is_duplicate(a, (int)number))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	if (!add_to_stack(a, (int)number))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return (1);
}

int	process_single_argument(char *arg, t_list **a)
{
	char	**numbers;
	int		i;
	int		result;

	numbers = ft_split(arg, ' ');
	if (!numbers)
		return (0);
	i = 0;
	result = 1;
	while (numbers[i] && result)
	{
		result = add_number_to_stack(a, numbers[i]);
		i++;
	}
	i = 0;
	while (numbers[i])
	{
		free(numbers[i]);
		i++;
	}
	free(numbers);
	if (!result)
		free_stack(a);
	return (result);
}

int	process_arguments(int argc, char **argv)
{
	t_list	**a;
	int		i;

	a = stack_a();
	if (argc == 2)
		return (process_single_argument(argv[1], a));
	i = 1;
	while (i < argc)
	{
		if (!add_number_to_stack(a, argv[i]))
		{
			free_stack(a);
			return (0);
		}
		i++;
	}
	return (1);
}
