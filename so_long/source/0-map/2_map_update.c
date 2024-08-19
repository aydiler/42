/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_map_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:28:24 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/19 20:07:43 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

static void	read_map(t_game *game, int fd);
static void	allocate_map_line(t_game *game, char ***map,
				int *height, char *line);

void init_map(t_game *game, char *path)
{
    int fd;
    char *line;

    fd = open(path, O_RDONLY);
    printf("Debug: File descriptor: %d\n", fd);
    if (fd < 0)
    {
        printf("Error\nInvalid file\n");
        exit(1);
    }

    // Read and print each line
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Debug: Line read: %s", line);
        free(line);
    }

    // Reset file pointer to the beginning
    lseek(fd, 0, SEEK_SET);

    read_map(game, fd);
    line_validation(game->plot.map, game);
    printf("Debug: After line_validation\n");

    // Add checks before accessing game->plot.map
    if (game->plot.map == NULL)
    {
        printf("Error: game->plot.map is NULL\n");
        endgame("Invalid map: NULL", game, error);
    }
    if (game->plot.map[0] == NULL)
    {
        printf("Error: game->plot.map[0] is NULL\n");
        endgame("Invalid map: Empty", game, error);
    }

    printf("Debug: About to calculate plot length\n");
    game->plot.length = ft_strlen(game->plot.map[0]);
    printf("Debug: Plot length calculated: %d\n", game->plot.length);

    close(fd);
    printf("Debug: File closed\n");
    printf("Debug: Exiting init_map\n");
}



static void allocate_map_line(t_game *game, char ** *map, int *height, char *line)
{
    char    *new_line;

    printf("Debug: Allocating line: %s", line);

    new_line = line[ft_strlen(line) - 1] != '\n' ? ft_strjoin(line, "\n") : ft_strdup(line);
    if (!new_line)
        endgame("Memory allocation failed!", game, error);

    *map = ft_realloc(*map, *height * sizeof(char *), (*height + 2) * sizeof(char *));
    if (!*map)
    {
        free(new_line);
        endgame("Memory allocation failed!", game, error);
    }

    (*map)[*height] = new_line;
    (*map)[*height + 1] = NULL;
    (*height)++;

    free(line);  // Free the original line
    printf("Debug: Height after allocation: %d\n", *height);
}



static void read_map_lines(t_game *game, int fd, char ***map, int *height)
{
    char    *line;
    size_t  total_len;

    total_len = 0;
    *height = 0;
    *map = NULL;  // Initialize map to NULL

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Debug: Line read: %s", line);  // Debug print
        allocate_map_line(game, map, height, line);
        total_len += ft_strlen((*map)[*height - 1]);
    }

    printf("Debug: Final height: %d, Total length: %zu\n", *height, total_len);

    if (*height == 0)
        endgame("Error: No valid lines read from map file", game, error);

    game->plot.length = *height > 0 ? total_len / *height : 0;

    printf("Debug: Map reading complete. Height: %d, Length: %d\n", *height, game->plot.length);

    // Add more debug prints here to check the map content
    for (int i = 0; i < *height; i++)
    {
        printf("Debug: Map line %d: %s", i, (*map)[i]);
    }

    printf("Debug: Exiting read_map_lines function\n");
}


static void concatenate_map(t_game *game, char **map, int height)
{
    char    *string_map;
    int     i;
    size_t  total_len;

    printf("Debug: Entering concatenate_map\n");
    
    total_len = 0;
    for (i = 0; i < height; i++) {
        total_len += ft_strlen(map[i]);
    }
    
    printf("Debug: Calculated total_len: %zu\n", total_len);
    
    string_map = malloc(total_len + 1);
    if (string_map == NULL)
        endgame("Memory allocation failed!", game, error);
    
    string_map[0] = '\0';
    i = 0;
    while (i < height)
    {
        ft_strlcat(string_map, map[i], total_len + 1);
        i++;
    }
    
    printf("Debug: Concatenated map: %s\n", string_map);
    
    game->i = start_counter(string_map, game);
    
    // Print all members of t_counter
    printf("Debug: start_counter returned: empty=%d, collectible=%d, exit=%d, start=%d, movements=%d\n",
           game->i.empty, game->i.collectible, game->i.exit, game->i.start, game->i.movements);
    
    free(string_map);
    printf("Debug: Exiting concatenate_map\n");
}


static void read_map(t_game *game, int fd)
{
    char    **map;
    int     height;

    map = NULL;
    height = 0;
    read_map_lines(game, fd, &map, &height);
    printf("Debug: After read_map_lines, map=%p, height=%d\n", (void*)map, height);
    
    game->plot.map = map;
    game->plot.height = height;
    
    printf("Debug: About to call concatenate_map\n");
    concatenate_map(game, map, height);
    printf("Debug: After concatenate_map\n");
    
    printf("Debug: game->plot.map=%p, game->plot.height=%d\n", (void*)game->plot.map, game->plot.height);
}

