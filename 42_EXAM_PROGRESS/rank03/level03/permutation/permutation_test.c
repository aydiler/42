#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort_string(char *str, int str_len)
{
	for(int i = 0; i < str_len; i++)
	{
		for(int j = 0; j < str_len - 1; j++)
		{
			if(str[j] > str[j+1])
				swap(&str[j], &str[j+1]);
		}
	}
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

int next_permutation(char *str, int str_len)
{
	int i = str_len - 2;
	while(i >= 0 && str[i] >= str[i+1])
		i--;
	if(i < 0)
		return 0;
	int j = str_len - 1;
	while(str[j] <= str[i])
		j--;
	swap(&str[i], &str[j]);
	reverse(str, i + 1, str_len - 1);
	return 1;
}

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;
	char *str = argv[1];
	int str_len = strlen(str);
	if (str_len == 0)
		return 0;
	sort_string(str, str_len);
	puts(str);
	while(next_permutation(str, str_len))
		puts(str);
	return 0;
}


