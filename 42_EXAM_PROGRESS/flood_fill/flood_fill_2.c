#include "flood_fill.h"

void fill(char **tab, t_point size, t_point current, char to_fill)
{
	if((current.x >= size.x) || (current.y >= size.y) || (current.x < 0) || (current.y < 0) || (tab[current.y][current.x] != to_fill))
		return ;
	tab[current.y][current.x] = 'F';
	fill(tab, size, (t_point){current.x + 1, current.y}, to_fill);
	fill(tab, size, (t_point){current.x - 1, current.y}, to_fill);
	fill(tab, size, (t_point){current.x, current.y + 1}, to_fill);
	fill(tab, size, (t_point){current.x, current.y - 1}, to_fill);
}

void flood_fill(char **tab, t_point size, t_point begin)
{
	fill(tab, size, begin, tab[begin.y][begin.x]);
}
