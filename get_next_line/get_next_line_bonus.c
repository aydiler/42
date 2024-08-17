/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:43:14 by adiler            #+#    #+#             */
/*   Updated: 2024/01/28 19:20:50 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*create_new_node(char *buffer, int start, int len)
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
	new_node->line = line;
	new_node->next = NULL;
	return (new_node);
}

t_list	*split_and_store_line(t_list **head, char *buffer)
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
		if (len > 0 || buffer[i] == '\n')
		{
			if (buffer[i] == '\n')
				len++;
			new_node = create_new_node(buffer, start, len);
			if (!new_node)
				return (NULL);
			ft_lstadd_back(head, new_node);
		}
		if (buffer[i])
			i++;
	}
	return (new_node);
}

int	read_split_and_store_line(int fd, t_list **head)
{
	int		bytes_read;
	char	*buf;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(buf);
		if (bytes_read == 0)
			return (0);
		else
			return (-1);
	}
	buf[bytes_read] = '\0';
	if (!split_and_store_line(head, buf))
	{
		free(buf);
		return (-1);
	}
	free(buf);
	return (bytes_read);
}

char	*pop_and_join(t_list **head, char *line)
{
	t_list	*first;
	char	*temp_line;
	char	*new_line;

	if (head == NULL || *head == NULL)
		return (line);
	first = *head;
	temp_line = first->line;
	*head = first->next;
	free(first);
	new_line = ft_strjoin(line, temp_line);
	free(line);
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
			handle_read_result(read_result, &fd_lists[fd], &line);
			if (read_result == 0)
				return (line);
		}
		line = pop_and_join(&fd_lists[fd], line);
		if (!line || ft_strchr(line, '\n'))
			break ;
	}
	return (line);
}

// void print(const char *str) {
// 	if (str == NULL) {
// 		printf("(null)\n");
// 		return;
// 	}
// 	for (int i = 0; str[i] != '\0'; ++i) {
// 		if (str[i] == '\n') {
// 			printf("\\n");
// 		} else {
// 			putchar(str[i]);
// 		}
// 	}
// 	printf("\n");
// }
// int main()
// {
// 	int	fd1;
// 	int fd2;
// 	fd1 = open("test1.txt", O_RDONLY);
// 	fd2 = open("test2.txt", O_RDONLY);

// 	char *line;
// 	line = get_next_line(fd1);
// 	printf("Returned line from fd1: \n");
// 	print(line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("Returned line from fd2: \n");
// 	print(line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("Returned line from fd1: \n");
// 	print(line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("Returned line from fd2: \n");
// 	print(line);
// 	free(line);
// 	// for (int i = 0; i < 10; ++i) {
// 	// 	line = get_next_line(fd);
// 	// 	printf("Returned line: \n");
// 	// 	print(line);
// 	// 	free(line);
// 	// }
// }
// void print_list(t_list *list) {
// 	while (list) {
// 		printf("List Node:\n"); // Assuming each node has a 'line' member
// 		print(list->line);
// 		list = list->next;
// 	}
// }