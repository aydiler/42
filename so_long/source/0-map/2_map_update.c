/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_map_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 20:11:33 by anhigo-s          #+#    #+#             */
/*   Updated: 2024/05/21 20:55:52 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void			read_map(t_game *game, int fd);
static t_counter	start_counter(char *string_map, t_game *game);
static void			count_elements(t_counter *cnt, char c);
char 				*strjoinfree(char *s1, char *s2);


void	init_map(t_game *game, char *path)
{
	int	fd;

	fd = open_file(path);
	read_map(game, fd);
	game->plot.length = len_map_validation(game->plot.map, game);
	close(fd);
	return ;
}

static void read_map(t_game *game, int fd)
{
    char *line;
    int height = 0;
    char **map = NULL;
    char **temp;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Read line: '%s'\n", line);
        temp = realloc(map, (height + 1) * sizeof(char *));
        if (temp == NULL)
        {
            // Handle realloc failure: free previously allocated memory and exit
            for (int i = 0; i < height; i++)
            {
                free(map[i]);
            }
            free(map);
            endgame("Memory allocation failed!", game, error);
        }
        map = temp;

        // Check if the line ends with a newline character
        if (line[strlen(line) - 1] != '\n')
        {
            // If not, append a newline character
            char *line_with_newline = malloc(strlen(line) + 2);
            strcpy(line_with_newline, line);
            strcat(line_with_newline, "\n");
            free(line);
            line = line_with_newline;
        }

        map[height] = line;
        height++;
    }
    game->plot.map = map;
    game->plot.height = height;

    // Concatenate all lines into a single string for start_counter
    int len = 0;
    for (int i = 0; i < height; i++)
    {
        len += strlen(map[i]); // No need for +1 since newline is now included
    }
    char *string_map = malloc(len + 1); // +1 for '\0'
    if (string_map == NULL)
    {
        endgame("Memory allocation failed!", game, error);
    }
    string_map[0] = '\0';
    for (int i = 0; i < height; i++)
    {
        strcat(string_map, map[i]);
    }
    game->i = start_counter(string_map, game);

    // Free the concatenated string
    free(string_map);
}

static t_counter	start_counter(char *string_map, t_game *game)
{
	t_counter	cnt;
	int			i;

	cnt = new_counter();
	i = 0;
	while (string_map[i] != '\0')
	{
		if (is_double_line(string_map, i))
		{
			free(string_map);
			endgame("double line, Invalid file!", game, file_error);
		}
		count_elements(&cnt, string_map[i]);
		i++;
	}
	is_elements_number_valid(game, &cnt, string_map);
	return (cnt);
}

static void	count_elements(t_counter *cnt, char c)
{
	if (c == 'C')
		cnt->collectible++;
	else if (c == 'E')
		cnt->exit++;
	else if (c == 'P')
		cnt->start++;
	else if (c == '0')
		cnt->empty++;
}