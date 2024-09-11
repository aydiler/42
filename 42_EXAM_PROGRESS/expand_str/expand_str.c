#include <unistd.h>

int is_space(char c)
{
	if (c == ' ' || c == '\t')
	{
		return 1;
	}
	return 0;
}
int main(int argc, char **argv)
{
	char *str = argv[1];
	int i = 0;
	int word_found = 0;

	if(argc != 2)
	{
		write(1, "\n", 1);
		return 0;
	}

	while(is_space(str[i]))
	{
		i++;
	}
	
	while(str[i])
	{
		if(!is_space(str[i]))
		{
			if(word_found)
			{
				write(1, "   ", 3);	
			}
			while(str[i] && !is_space(str[i]))
			{
				write(1, &str[i], 1);
				i++;
			}
			word_found = 1;
		}
		else
			i++;
	}
	write(1, "\n", 1);
}
