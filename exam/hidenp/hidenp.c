#include <unistd.h>

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		write(1, "\n", 1);
		return 0;
	}
	char *str1 = argv[1];
	char *str2 = argv[2];

	int i = 0;
	int j = 0;
	while(str2[j])
	{
		if(str1[i] == str2[j])
		{ 
			i++;
			j++;
			if(!str1[i])
			{
				write(1, "1\n", 2);
				return 1;
			}
		}
		else
		{
			j++;
		}
	}
	write(1, "0\n", 2);
	return 0;
}
