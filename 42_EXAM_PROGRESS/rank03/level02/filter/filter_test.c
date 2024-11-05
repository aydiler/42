#define BUFFER_SIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strncmp(char *str1, char *str2, int len)
{
	while(len > 0 && (*str1 || *str2))
	{
		if (*str1 != *str2)
		{
			return *str1 - *str2;
		}
		str1++;
		str2++;
		len--;
	}
	return 0;
}

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

int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	char buff[BUFFER_SIZE];
	int read_size;
	char *target = argv[1];
	int target_len = ft_strlen(target);

	while((read_size = read(0, buff, BUFFER_SIZE)) > 0)
	{
		if(read_size < target_len)
		{
			write(1, buff, read_size);
			continue ;
		}
		int i = 0;
		while(i <= read_size - target_len)
		{
			if(ft_strncmp(target, &buff[i], target_len) == 0)
			{
				int j = 0;
				while(j < target_len)
				{
					write(1, "*", 1);
					j++;
				}
				i = i + target_len;
			}
			else
			{
				write(1, &buff[i], 1);
				i++;
			}
		}
		write(1, &buff[i], read_size - i);
	}
	return 0;
}
