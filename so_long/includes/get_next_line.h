/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:40:31 by adiler            #+#    #+#             */
/*   Updated: 2024/05/21 18:22:05 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "so_long.h"

typedef struct s_list_l
{
	char			*line;
	struct s_list_l	*next;
}	t_list_l;
char	*get_next_line(int fd);
char	*ft_strjoin_c(char const *s1, char const *s2);
void	ft_lstadd_back_c(t_list_l **lst, t_list_l *new_node);
void	handle_read_result(int result, t_list_l **head, char **line);

#endif