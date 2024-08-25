/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:05 by adiler            #+#    #+#             */
/*   Updated: 2024/08/19 17:32:30 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	handle_read_result(int result, t_list **head, char **line)
{
	t_list	*tmp;

	if (result <= 0)
	{
		while (*head)
		{
			tmp = (*head)->next;
			free((*head)->content);
			free(*head);
			*head = tmp;
		}
		if (result == 0)
			return ;
		free(*line);
		*line = NULL;
	}
}
