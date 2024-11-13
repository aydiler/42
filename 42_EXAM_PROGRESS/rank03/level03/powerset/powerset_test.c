#include <stdlib.h>
#include <stdio.h>

void powerset(int size, int *current, int curr_size, int start)
{
	for(int i = start; i < size; i++)
	{
		current[curr_size] = i;
		for(int i = 0; i<=curr_size; i++)
			printf("%d", current[i]);
		printf("\n");
		powerset(size, current, curr_size + 1, i + 1);
	}
}

int main()
{
	int size = 5;
	int *current = malloc(sizeof(int) * size);
	if(!current)
		return 1;

	powerset(size, current, 0, 0);

	free(current);
}
