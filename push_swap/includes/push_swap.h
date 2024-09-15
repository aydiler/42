/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:43:21 by adiler            #+#    #+#             */
/*   Updated: 2024/09/14 20:17:06 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "./libft/libft.h"
# include "./printf/ft_printf.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

t_list		**stack_a(void);
t_list		**stack_b(void);
void		free_stack(t_list **stack);
int			process_arguments(int argc, char **argv);
int			add_to_stack(t_list **stack, int number);
int			is_valid_int_string(const char *str);
// void		print_stacks(t_list *a, t_list *b);
void		ft_pa(void);
void		ft_pb(void);
void		ft_ra(void);
void		ft_rb(void);
void		ft_rr(void);
void		ft_rra(void);
void		ft_rrb(void);
void		ft_rrr(void);
void		ft_sa(void);
void		ft_sb(void);

#endif
