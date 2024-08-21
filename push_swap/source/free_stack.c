#include "../includes/push_swap.h"

void	free_stack(t_list **stack)
{
	t_list	*current;
	t_list	*next;

	if (stack == NULL || *stack == NULL)
		return ;
	current = *stack;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*stack = NULL;
}
