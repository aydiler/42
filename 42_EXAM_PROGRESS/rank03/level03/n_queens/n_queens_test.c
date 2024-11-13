#include <stdio.h>
#include <stdlib.h>

int n;
int pos[20];

int is_safe(int row, int col)
{
	int i = 0;
	while(i < col)
	{
		if(pos[i] == row || pos[i] - row == i - col || row - pos[i] == i - col)
			return 0;
		i++;
	}
	return 1;
}

void print()
{
	int i = 0;
	while (i < n)
	{
		printf("%d", pos[i]);
		if(i < n - 1)
			printf(" ");
		else
			printf("\n");
		i++;
	}
}

void solve(int col)
{
	if(col == n)
	{
		print();
		return ;
	}
	int row = 0;
	while (row < n)
	{
		if(is_safe(row, col))
		{
			pos[col] = row;
			solve(col + 1);
		}
		row++;
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
