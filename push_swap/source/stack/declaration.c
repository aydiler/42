#include "../includes/push_swap.h"

t_stack	*stack_a(void)
{
	static t_stack	stack;

	return (&stack);
}

t_stack	*stack_b(void)
{
	static t_stack	stack;

	return (&stack);
}