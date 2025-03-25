#include <stdio.h>
#include <unistd.h>

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

int power(int base, int exp)
{
	int result = 1;
	if(exp == 0)
		return result;
	while(exp > 0)
	{
		result = result * base;
		exp--;
	}
	return result;
}

int atoi(char *str)
{
	int num = 0;
	int len = ft_strlen(str);
	while(*str)
	{
		num = num + ((*str - '0') * power(10, len-1));
		len--;
		str++;  
	}
	return num;
}

int is_prime(int num)
{
	int count = 2;
	int prime = 1;
	while(count < num)
	{
		if(num%count == 0)
		{
			prime = 0;
			break ;
		}
		else
			count++;
	}
	return prime;
}

int intlen(int num)
{
	int len = 0;
	while(num != 0)
	{
		num /= 10;
		len++;
	}
	return len;
}

void print_num(int num)
{
	int len = intlen(num);
	char num_c;
	int temp;
	while(len > 0)
	{
		temp = num / power(10, len - 1);
		//printf("temp: %d\n", temp);
		num_c = temp%10 + '0';
		//printf("num_c: %d\n", num_c);
		write(1, &num_c, 1);
		len--;
	}
}

int main(int argc, char **argv)
{
	if(argc != 2 || argv[1][0] == '-' || atoi(argv[1]) == 0 || atoi(argv[1]) == 1)
	{
		write(1, "0\n", 2);
		return 0;
	}
	char *str = argv[1];
	int num = atoi(str);
	int i = 2;
	int result = 0;
	while(i <= num)
	{
		if(is_prime(i))
			result = result + i;
		i++;
	}
	//printf("result: %d\n", result);
	print_num(result);
	write(1, "\n", 1);
	return 0;
}
