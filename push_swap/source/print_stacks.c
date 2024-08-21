#include "../includes/push_swap.h"

static int	get_stack_size(t_stack *stack)
{
	int		size;
	t_list	*current;

	size = 0;
	current = stack->head;
	while (current)
	{
		size++;
		current = current->next;
	}
	return (size);
}

static int	get_max_size(int size_a, int size_b)
{
	if (size_a > size_b)
		return (size_a);
	return (size_b);
}

static void	print_element(t_list *current, int size, int i)
{
	int	j;

	j = 0;
	while (j < size - i - 1)
	{
		current = current->next;
		j++;
	}
	printf("%-4d", (int)(intptr_t)current->content);
}

void	print_stacks(t_stack *a, t_stack *b)
{
	int		size_a;
	int		size_b;
	int		max_size;
	int		i;
	t_list	*current_a;
	t_list	*current_b;

	size_a = get_stack_size(a);
	size_b = get_stack_size(b);
	max_size = get_max_size(size_a, size_b);
	printf("-------------------\n");
	current_a = a->head;
	current_b = b->head;
	i = max_size - 1;
	while (i >= 0)
	{
		if (i < size_a)
			print_element(current_a, size_a, i);
		else
			printf("     ");
		if (i < size_b)
			print_element(current_b, size_b, i);
		printf("\n");
		i--;
	}
	printf("_   _\n");
	printf("a   b\n");
	printf("-------------------\n");
}
