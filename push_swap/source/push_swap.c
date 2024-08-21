#include "../includes/push_swap.h"

static int	get_max_bits(t_list *stack)
{
	t_list	*current;
	long	max;
	int		max_bits;

	current = stack;
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

static void	radix_sort_bit(t_list **a, t_list **b, int bit)
{
	int		size;
	int		i;
	long	num;

	size = ft_lstsize(*a);
	i = 0;
	while (i < size)
	{
		num = (long)(*a)->content;
		if (((num >> bit) & 1) == 1)
			ft_ra();
		else
			ft_pb();
		i++;
	}
	while (*b)
		ft_pa();
}

void	radix_sort(t_list **a, t_list **b)
{
	int	max_bits;
	int	i;

	max_bits = get_max_bits(*a);
	i = 0;
	while (i < max_bits)
	{
		radix_sort_bit(a, b, i);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_list	**a;
	t_list	**b;

	if (argc < 2)
		return (1);
	a = stack_a();
	b = stack_b();
	if (!process_arguments(argc, argv))
		return (1);
	radix_sort(a, b);
	print_stacks(*a, *b);
	free_stack(a);
	free_stack(b);
	return (0);
}
