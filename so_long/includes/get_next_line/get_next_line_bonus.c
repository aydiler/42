/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 18:43:14 by adiler            #+#    #+#             */
/*   Updated: 2024/08/19 19:48:20 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list *create_new_node(char *buffer, int start, int len)
{
    char    *line;
    t_list  *new_node;
    int     i;

    printf("Debug: Entering create_new_node with start=%d, len=%d\n", start, len);
    line = malloc(sizeof(char) * (len + 1));
    if (!line)
    {
        printf("Debug: Failed to allocate memory for line\n");
        return (NULL);
    }
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
        printf("Debug: Failed to allocate memory for new_node\n");
        free(line);
        return (NULL);
    }
    new_node->content = line;
    new_node->next = NULL;
    printf("Debug: Created new node with content: %s\n", line);
    return (new_node);
}



t_list *split_and_store_line(t_list **head, char *buffer)
{
    printf("Debug: split_and_store_line function entered\n");
    size_t  i;
    t_list  *new_node;
    size_t  start;
    size_t  len;

    i = 0;
    printf("Debug: Entering split_and_store_line with buffer: %s\n", buffer);
    while (buffer[i])
    {
        start = i;
        while (buffer[i] && buffer[i] != '\n')
            i++;
        len = i - start + (buffer[i] == '\n' ? 1 : 0);
        printf("Debug: Found line segment: %.*s\n", (int)len, buffer + start);
        if (len > 0)
        {
            new_node = create_new_node(buffer, start, len);
            if (!new_node)
            {
                printf("Debug: Failed to create new node\n");
                return (NULL);
            }
            ft_lstadd_back(head, new_node);
            printf("Debug: Added node with content: %.*s\n", (int)len, (char *)new_node->content);
        }
        if (buffer[i])
            i++;
    }
    printf("Debug: Finished split_and_store_line, nodes created: %d\n", ft_lstsize(*head));
    return (*head);
}

int read_split_and_store_line(int fd, t_list **head)
{
    int     bytes_read;
    char    *buf;
    t_list  *result;

    printf("Debug: Entering read_split_and_store_line for fd %d\n", fd);
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
    {
        printf("Debug: Failed to allocate buffer\n");
        return (-1);
    }
    printf("Debug: Reading from fd %d\n", fd);
    bytes_read = read(fd, buf, BUFFER_SIZE);
    printf("Debug: bytes_read = %d\n", bytes_read);
    if (bytes_read <= 0)
    {
        free(buf);
        printf("Debug: Read error or EOF (bytes_read = %d)\n", bytes_read);
        return (bytes_read);
    }
    buf[bytes_read] = '\0';
    printf("Debug: Read content: %s\n", buf);
    printf("Debug: About to call split_and_store_line\n");
    result = split_and_store_line(head, buf);
    printf("Debug: split_and_store_line call completed\n");
    printf("Debug: split_and_store_line returned %p\n", (void *)result);
    if (!result)
    {
        free(buf);
        printf("Debug: Failed to split and store line\n");
        return (-1);
    }
    printf("Debug: After split_and_store_line, head = %p\n", (void *)*head);
    free(buf);
    return (bytes_read);
}


char    *pop_and_join(t_list ** head, char *line)
{
    t_list    *first;
    char    *temp_line;
    char    *new_line;

    printf("Debug: Entering pop_and_join\n");
    if (head == NULL || *head == NULL)
    {
        printf("Debug: No data to pop\n");
        return (line);
    }
    first = *head;
    temp_line = (char *)first->content;
    *head = first->next;
    free(first);
    printf("Debug: Popped content: %s\n", temp_line);
    if (line == NULL)
    {
        new_line = ft_strdup(temp_line);
    }
    else
    {
        new_line = ft_strjoin(line, temp_line);
        free(line);
    }
    free(temp_line);
    if (!new_line)
    {
        printf("Debug: Failed to create new_line\n");
        return (NULL);
    }
    printf("Debug: Returning new_line: %s\n", new_line);
    return (new_line);
}

char *get_next_line(int fd)
{
    printf("Debug: BUFFER_SIZE = %d\n", BUFFER_SIZE);
    static t_list    *fd_lists[MAX_FD];
    char            *line;
    int             read_result;

    line = NULL;
    if (fd < 0 || fd >= MAX_FD)
        return (NULL);
    printf("Debug: Entering get_next_line for fd %d\n", fd);
    printf("Debug: fd_lists[fd] before reading: %p\n", (void *)fd_lists[fd]);
    while (1)
    {
        if (!fd_lists[fd])
        {
            printf("Debug: No stored data for fd %d, reading from file\n", fd);
            read_result = read_split_and_store_line(fd, &fd_lists[fd]);
            printf("Debug: Immediately after read_split_and_store_line\n");
            printf("Debug: read_result = %d\n", read_result);
            printf("Debug: fd_lists[fd] after reading: %p\n", (void *)fd_lists[fd]);
            if (read_result <= 0)
            {
                printf("Debug: End of file or read error\n");
                return (line);
            }
        }
        if (fd_lists[fd] == NULL)
        {
            printf("Debug: fd_lists[fd] is NULL after reading\n");
            return (line);
        }
        line = pop_and_join(&fd_lists[fd], line);
        printf("Debug: After pop_and_join, line = %s\n", line ? line : "NULL");
        if (!line || ft_strchr(line, '\n'))
            break;
    }
    printf("Debug: Returning line: %s\n", line ? line : "NULL");
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