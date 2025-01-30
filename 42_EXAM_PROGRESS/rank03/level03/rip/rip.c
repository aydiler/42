#include <stdio.h>
#include <string.h>

// Function to check if the string is balanced
int	is_valid(const char *str)
{
	int	count;

	count = 0;
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			count++;
		if (str[i] == ')')
			count--;
		if (count < 0)
			return (0);
	}
	if (count == 0)
		return (1);
	return (0);
}

// Recursive function to generate all valid strings by removing invalid parentheses
void	find_solutions(char *str, int pos, int open_to_remove,
		int close_to_remove)
{
	char	orig;

	if (str[pos] == '\0')
	{
		if (is_valid(str))
			puts(str);
		return ;
	}
	// Try removing an open parenthesis if needed
	if (open_to_remove > 0 && str[pos] == '(')
	{
		orig = str[pos];
		str[pos] = ' ';
		find_solutions(str, pos + 1, open_to_remove - 1, close_to_remove);
		str[pos] = orig;
	}
	// Try removing a close parenthesis if needed
	if (close_to_remove > 0 && str[pos] == ')')
	{
		orig = str[pos];
		str[pos] = ' ';
		find_solutions(str, pos + 1, open_to_remove, close_to_remove - 1);
		str[pos] = orig;
	}
	// Continue without removing the current character
	find_solutions(str, pos + 1, open_to_remove, close_to_remove);
}

int	main(int argc, char *argv[])
{
	int	open = 0, close = 0;
	if (argc != 2)
		return (1);
	char *str = argv[1];
	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			open++;
		if (str[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
	}
	printf("open: %d, close: %d\n", open, close);
	find_solutions(str, 0, open, close);
	return (0);
}
