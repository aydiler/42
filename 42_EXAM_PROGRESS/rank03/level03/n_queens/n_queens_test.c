#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int n;
int pos[20];

int is_safe(int row, int col)
{
	for(int i = 0; i < col; i++)
	{
		if(pos[i] == row || pos[i] - row == i - col || row - pos[i] == i - col)
			return 0;
	}
	return 1;
}

void solve(int col)
{
	if(col == n)
	{
		for(int i = 0; i < n; i++)
		{
			printf("%d", pos[i]);
			if(i < n - 1)
				printf(" ");
		}
		printf("\n");
	}
	for(int row = 0; row < n; row++)
	{
		if(is_safe(row, col))
		{
			pos[col] = row;
			solve(col + 1);
		}
	}
}

int main(int argc, char **argv)
{
	if(argc == 2)
	{
		n = atoi(argv[1]);
		solve(0);
	}
	return 0;
}
