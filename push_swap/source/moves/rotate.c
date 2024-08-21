#include "../../includes/push_swap.h"

static void	ft_rotate(t_list **head)
{
	t_list	*temp;
	t_list	*cur;

	if (!head || !*head || !(*head)->next)
		return ;
	temp = *head;
	*head = (*head)->next;
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = temp;
	temp->next = NULL;
}

void	ft_ra(void)
{
	ft_rotate(stack_a());
	write(1, "ra\n", 3);
}

void	ft_rb(void)
{
	ft_rotate(stack_b());
	write(1, "rb\n", 3);
}

void	ft_rr(void)
{
	ft_rotate(stack_a());
	ft_rotate(stack_b());
	write(1, "rr\n", 3);
}
