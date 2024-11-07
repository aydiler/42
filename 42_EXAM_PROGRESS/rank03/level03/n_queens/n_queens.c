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

void solve(int col)
{
	if(col == n)
	{
		print_pos();
	}
	int row = 0;
	while(row < n)
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
		n = atoi[1];
		solve(0);
	}
	return 0;
}
