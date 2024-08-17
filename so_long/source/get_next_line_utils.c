/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:18:05 by adiler            #+#    #+#             */
/*   Updated: 2024/05/21 19:35:27 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_strjoin_c(char const *s1, char const *s2)
{
	char	*str;
	int		len1;
	int		len2;

	len1 = 0;
	len2 = 0;
	while (s1 && s1[len1])
		len1++;
	while (s2 && s2[len2])
		len2++;
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	return (str);
}

void	ft_lstadd_back_c(t_list_l **lst, t_list_l *new_node)
{
	t_list_l	*current;

	if (lst == NULL)
		return ;
	else if (*lst == NULL)
		*lst = new_node;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	handle_read_result(int result, t_list_l **head, char **line)
{
	t_list_l	*tmp;

	if (result <= 0)
	{
		while (*head)
		{
			tmp = (*head)->next;
			free((*head)->line);
			free(*head);
			*head = tmp;
		}
		if (result == 0)
			return ;
		free(*line);
		*line = NULL;
	}
}