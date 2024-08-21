#include "../../includes/push_swap.h"

static int	add_to_stack(t_stack *stack, int number)
{
	t_list	*new_node;

	new_node = ft_lstnew((void *)(intptr_t)number);
	if (!new_node)
		return (0);
	ft_lstadd_back(&(stack->head), new_node);
	return (1);
}

int	process_arguments(int argc, char **argv)
{
	int		i;
	int		number;
	t_stack	*a;

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