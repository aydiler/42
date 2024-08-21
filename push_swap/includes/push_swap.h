#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include "./printf/ft_printf.h"

# include <fcntl.h>//open, O_RDONLY
# include <unistd.h>//read, close, write
# include <stdlib.h>//malloc
# include <stdio.h>//printf
# include <stdbool.h>//bool

typedef struct s_stack
{
	t_list	*head;
}	t_stack;

t_stack		*stack_a(void);
t_stack		*stack_b(void);
void		free_stack(t_stack *stack);
int			process_arguments(int argc, char **argv);
void		print_stacks(t_stack *a, t_stack *b);
void		ft_pa(void);
void		ft_pb(void);
#endif