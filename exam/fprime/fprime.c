#include <stdio.h>
#include <stdlib.h>

void fprime(int num)
{
	int first = 1;
	int div = 2;

	if (num == 1)
		printf("1");

	while (num >= div)
	{
		if (num % div == 0)
		{
			if (first)
			{
				printf("%d", div);
				first = 0;
			}
			else
				printf("*%d", div);
			num = num / div;
		}
		else
			div++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		fprime(atoi(argv[1]));
	}
	printf("\n");
	return 0;
}
