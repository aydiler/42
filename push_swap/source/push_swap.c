#include "../includes/push_swap.h"

int	main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	if (!process_arguments(argc, argv))
		return (1);
	// print_stacks(stack_a(), stack_b());
	ft_pb();
	ft_pb();
	ft_pb();
	ft_pb();
	ft_pb();
	print_stacks(stack_a(), stack_b());
	// ft_ra();
	// ft_rb();
	// print_stacks(stack_a(), stack_b());
	// ft_rr();
	// print_stacks(stack_a(), stack_b());
	// ft_rra();
	// print_stacks(stack_a(), stack_b());
	// ft_rrb();
	// print_stacks(stack_a(), stack_b());
	// ft_rrr();
	// print_stacks(stack_a(), stack_b());
	ft_sa();
	ft_sb();
	print_stacks(stack_a(), stack_b());
	free_stack(stack_a());
	free_stack(stack_b());
	return (0);
}