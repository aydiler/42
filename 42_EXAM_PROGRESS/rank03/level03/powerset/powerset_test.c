#include <stdio.h>
#include <stdlib.h>

void print_subset(int *numbers, int *pos, int subsize)
{
	int i = 0;
	while(i < subsize)
	{
		printf("%d ", numbers[pos[i]]);
		i++;
	}
	printf("\n");
}

void solve(int target, int *numbers, int size, int *pos, int subsize, int start, int sum)
{
	if (sum == target && subsize > 0)
		print_subset(numbers, pos, subsize);
	int i = start;
	while (i < size)
	{
		pos[subsize] = i;
		solve(target, numbers, size, pos, subsize + 1, i + 1, sum + numbers[i]);
		i++;
	}
	
}

int main(int argc, char **argv)
{
	if (argc < 3)
		return 0;
	int target = atoi(argv[1]);
	int size = argc - 2;
	int numbers[size];
	int pos[size];
	int i = 0;
	while (i < size)
	{
		numbers[i] = atoi(argv[i + 2]);
		i++;
	}
	solve(target, numbers, size, pos, 0, 0, 0);
	return 0;
}
