#include <unistd.h>
#include <stdio.h>

void *replace(char *str, char a, char b)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == a)
			str[i] = b;
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

int main (int argc, char **argv)
{
	if(argc != 4)
	{
		write(1, "\n", 1);
		return 0;
	}
	if(argv[2][1] || argv[3][1])
	{
		write(1, "\n", 1);
		return 0;
	}
	replace(argv[1], argv[2][0], argv[3][0]);
}
