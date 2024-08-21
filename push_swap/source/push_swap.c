#include "../includes/push_swap.h"

static int	get_max_bits(t_stack *stack)
{
	t_list	*current;
	long	max;
	int		max_bits;

	current = stack->head;
	max = 0;
	while (current)
	{
		if ((long)current->content > max)
			max = (long)current->content;
		current = current->next;
	}
	max_bits = 0;
	while ((max >> max_bits) != 0)
		max_bits++;
	return (max_bits);
}

static void	radix_sort_bit(t_stack *a, t_stack *b, int bit)
{
	int		size;
	int		i;
	long	num;

	size = ft_lstsize(a->head);
	i = 0;
	while (i < size)
	{
		num = (long)a->head->content;
		if (((num >> bit) & 1) == 1)
			ft_ra();
		else
			ft_pb();
		i++;
	}
	while (b->head)
		ft_pa();
}

void	radix_sort(t_stack *a, t_stack *b)
{
	int	max_bits;
	int	i;

	max_bits = get_max_bits(a);
	i = 0;
	while (i < max_bits)
	{
		radix_sort_bit(a, b, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (!process_arguments(argc, argv))
		return (1);
	radix_sort(stack_a(), stack_b());
	print_stacks(stack_a(), stack_b());
	free_stack(stack_a());
	free_stack(stack_b());
	return (0);
}
