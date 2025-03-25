#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int len = 0;
	while(*str)
	{
		len++;
		str++;
	}
	return len;
}

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void reverse(char *str, int start, int end)
{
	while(start < end)
	{
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

void sort_string(char *str)
{
	int len = ft_strlen(str);
	for(int i = 0; i < len - 1; i++)
	{
		for(int j = 0; j < len - 1; j++)
		{
			if(str[j] > str[j + 1])
				swap(&str[j], &str[j+1]);
		}
	}
}

int next_permutation(char *str)
{
	int len = ft_strlen(str);
	int i = len - 2;

	while(i >= 0 && str[i] >= str[i+1])
		i--;

	if(i < 0)
		return 0;

	int j = len - 1;
	while(str[i] > str[j])
		j--;

	swap(&str[i], &str[j]);

	reverse(str, i+1, len-1);

	return 1;
}

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	char *str = argv[1];

	sort_string(str);
	puts(str);
	while(next_permutation(str))
		puts(str);
	return 0;
}
