#include "../../includes/push_swap.h"

/* Top goest to bottom, anti clock wise*/
static void	ft_rotate(t_list **head)
{
	t_list	*temp;
	t_list	*cur;

	temp = *head;
	if (!head || !*head)
		return ;
	*head = (*head)->next;
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = temp;
	cur->next->next = NULL;
}

void	ft_ra(void)
{
	ft_rotate(&stack_a()->head);
	write(1, "ra\n", 3);
}

void	ft_rb(void)
{
	ft_rotate(&stack_b()->head);
	write(1, "rb\n", 3);
}

void	ft_rr(void)
{
	ft_rotate(&stack_a()->head);
	ft_rotate(&stack_b()->head);
	write(1, "rr\n", 3);
}