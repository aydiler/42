#include "../../includes/push_swap.h"

static int	ft_swap_elements(t_list **head)
{
	t_list	*first;
	t_list	*second;
	t_list	*rest;

	if (!head || !(*head) || !(*head)->next)
		return (1);
	first = *head;
	second = (*head)->next;
	rest = second->next;
	*head = second;
	second->next = first;
	first->next = rest;
	return (0);
}

void	ft_sa(void)
{
	if (ft_swap_elements(stack_a()) == 0)
		ft_printf("sa\n");
}

void	ft_sb(void)
{
	if (ft_swap_elements(stack_b()) == 0)
		ft_printf("sb\n");
}
