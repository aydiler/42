#include "../includes/push_swap.h"

void	free_stack(t_stack *stack)
{
	ft_lstclear(&(stack->head), NULL);
}