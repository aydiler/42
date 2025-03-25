#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int is_valid(char *str)
{
	int count = 0;
	while (*str)
	{
		if(*str == '(')
			count++;
		if(*str == ')')
			count--;
		if(count < 0)
			return 0;
		str++;
	}
	//printf("count: %d\n", count);
	if (count == 0)
	{
		//printf("is valid");
		return 1;
	}
	return 0;
}

void rip(char *str, int pos, int open, int close)
{
	if(str[pos] == '\0')
	{
		if(is_valid(str))
			puts(str);
		return ;
	}
	if(str[pos] == '(' && open > 0)
	{
		str[pos] = ' ';
		rip(str, pos + 1, open - 1, close);
		str[pos] = '(';
	}
	if(str[pos] == ')' && close > 0)
	{
		str[pos] = ' ';
		rip(str, pos + 1, open, close - 1);
		str[pos] = ')';
	}
	rip(str, pos+1, open, close);
}

int main(int argc, char **argv)
{
	int open, close;
	open = 0;
	close = 0;
	if (argc != 2)
		return 0;
	char *str = argv[1];
	int i = 0;
	while (str[i])
	{
		if(str[i] == '(')
			open++;
		if(str[i] == ')')
		{
			if (open > 0)
				open--;
			else
				close++;
		}
		i++;
	}
	printf("open: %d, close: %d\n", open, close);
	rip(str, 0, open, close);
	return 0;
}
