/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_map_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:28:30 by ubuntu            #+#    #+#             */
/*   Updated: 2024/08/18 22:49:15 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/so_long.h"

t_counter	new_counter(void)
{
	t_counter	counter;

	counter.collectible = 0;
	counter.start = 0;
	counter.exit = 0;
	counter.movements = 0;
	counter.empty = 0;
	return (counter);
}

void	line_validation(char **map, t_game *game)
{
	int		i;
	t_point	point;

	i = 0;
	point.x = 0;
	point.y = ft_strlen(map[0]);
	while (map[i] != 0)
	{
		point.x = ft_strlen(map[i]);
		// Print out the index, the line and its length
		printf("Line %d: '%s', length: %d\n", i, map[i], point.x);
		if (point.x != point.y)
		{
			// Also print out the expected length for comparison
			printf("Error: line %d length (%d) does not match expected length (%d)\n", i, point.x, point.y);
			free_map(game);
			endgame("Invalid file: lines are not the same size!", game, error);
		}
		i++;
	}
}

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

t_counter	start_counter(char *string_map, t_game *game)
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

void	count_elements(t_counter *cnt, char c)
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
