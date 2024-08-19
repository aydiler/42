/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:43:14 by adiler            #+#    #+#             */
/*   Updated: 2024/08/19 21:03:31 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*create_new_node(char *buffer, int start, int len)
{
	char	*line;
	t_list	*new_node;
	int		i;

	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = buffer[start + i];
		i++;
	}
	line[i] = 0;
	new_node = malloc(sizeof(t_list));
	if (!new_node)
	{
		free(line);
		return (NULL);
	}
	new_node->content = line;
	new_node->next = NULL;
	return (new_node);
}

static t_list	*split_and_store_line(t_list **head, char *buffer)
{
	size_t	i;
	t_list	*new_node;
	size_t	start;
	size_t	len;

	i = 0;
	while (buffer[i])
	{
		start = i;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		len = i - start;
		if (buffer[i] == '\n')
			len++;
		if (len > 0)
		{
			new_node = create_new_node(buffer, start, len);
			if (!new_node)
				return (NULL);
			ft_lstadd_back(head, new_node);
		}
		if (buffer[i])
			i++;
	}
	return (*head);
}

static int	read_split_and_store_line(int fd, t_list **head)
{
	int		bytes_read;
	char	*buf;
	t_list	*result;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buf);
		return (bytes_read);
	}
	buf[bytes_read] = '\0';
	result = split_and_store_line(head, buf);
	if (!result)
	{
		free(buf);
		return (-1);
	}
	free(buf);
	return (bytes_read);
}

static char	*pop_and_join(t_list **head, char *line)
{
	t_list	*first;
	char	*temp_line;
	char	*new_line;

	if (head == NULL || *head == NULL)
		return (line);
	first = *head;
	temp_line = (char *)first->content;
	*head = first->next;
	free(first);
	if (line == NULL)
		new_line = ft_strdup(temp_line);
	else
	{
		new_line = ft_strjoin(line, temp_line);
		free(line);
	}
	free(temp_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static t_list	*fd_lists[MAX_FD];
	char			*line;
	int				read_result;

	line = NULL;
	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	while (1)
	{
		if (!fd_lists[fd])
		{
			read_result = read_split_and_store_line(fd, &fd_lists[fd]);
			if (read_result <= 0)
				return (line);
		}
		if (fd_lists[fd] == NULL)
			return (line);
		line = pop_and_join(&fd_lists[fd], line);
		if (!line || ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}
