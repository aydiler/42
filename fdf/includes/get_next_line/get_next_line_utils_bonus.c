/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:05 by adiler            #+#    #+#             */
/*   Updated: 2024/08/19 17:50:48 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	handle_read_result(int result, t_list **fd_list, char **line)
{
	t_list	*tmp;

	if (result <= 0)
	{
		if (result == 0)
			return ;
		while (*fd_list)
		{
			tmp = (*fd_list)->next;
			free((*fd_list)->content);
			free(*fd_list);
			*fd_list = tmp;
		}
		free(*line);
		*line = NULL;
	}
}
