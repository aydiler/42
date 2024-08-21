#include "../includes/push_swap.h"

void	free_stack(t_stack *stack)
{
	t_list	*current;
	t_list	*next;

	if (stack == NULL || stack->head == NULL)
		return ;

	current = stack->head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	stack->head = NULL;
}
