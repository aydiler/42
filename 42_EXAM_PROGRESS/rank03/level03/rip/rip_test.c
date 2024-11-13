#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int is_valid(char *str)
{
	int balance = 0;
	for(int i = 0; str[i]; i++)
	{
		if(str[i] == '(') balance++;
		if(str[i] == ')') balance--;
		if(balance < 0)
			return 0;
	}
	return balance == 0;
}

void find_solutions(char *str, int pos, int to_remove, char remove_type)
{
	if(str[pos] == 0 || to_remove == 0)
	{
		if(is_valid(str))
			puts(str);
		return;
	}
	if(str[pos] == remove_type && to_remove > 0)
	{
		char orig = str[pos];
		str[pos] = ' ';
		find_solutions(str, pos + 1, to_remove - 1, remove_type);
		str[pos] = orig;
	}
	find_solutions(str, pos + 1, to_remove, remove_type);
}

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	char str[1000];
	strcpy(str, argv[1]);

	int open = 0, close = 0;
	for(int i = 0; str[i]; i++)
	{
		if(str[i] == '(') open++;
		if(str[i] == ')') close++;
	}
	int to_remove;
	char remove_type;
	if(open < close)
	{
		to_remove = close - open;
		remove_type = ')';
	}
	if(open > close)
	{
		to_remove = open - close;
		remove_type = '(';
	}

	find_solutions(str, 0, to_remove, remove_type);
	return 0;
}
