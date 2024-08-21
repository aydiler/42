#include "../includes/push_swap.h"

t_list	**stack_a(void)
{
	static t_list	*stack = NULL;

	return (&stack);
}

t_list	**stack_b(void)
{
	static t_list	*stack = NULL;

	return (&stack);
}