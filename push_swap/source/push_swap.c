#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (!process_arguments(argc, argv))
		return (1);
	ft_pb();
	ft_pb();
	print_stacks(stack_a(), stack_b());
	return (0);
}