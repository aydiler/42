#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int numlen(int num)
{
	int len = 0;

	if (num <= 0)
	{
		len++;
	}
	while (num != 0)
	{
		num /= 10;
		len++;
	}
	return len;
}

char *ft_itoa(int nbr)
{
	long num = nbr;
	char *str;
	int len = numlen(num);

	str = malloc(sizeof(char) * (len+1));
	if (!str)
		return NULL;
	if(num == 0)
	{
		str[0] = '0';
	}
	if(num < 0)
	{
		num = -num;
		str[0] = '-';
	}
	//printf("null pointer pos: %d\n", len);
	str[len] = 0;
	len--;
	while(num != 0)
	{
		str[len] = (num%10) + '0';
		//printf("str content at len %d: %c\n", len, str[len]);
		num /= 10;
		len--;
	}
	return str;
}

int main()
{
	int num = -234;
	printf("numlen: %d\n", numlen(num));
	printf("itoa: %s\n", ft_itoa(num));
}

