#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int is_space(char c)
{
	if(c == ' ' || c == '\t')
		return 1;
	return 0;
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		write(1, "\n", 1);
		return 0;
	}
	char *str = argv[1];
	//skip spaces
	while(is_space(*str))
		str++;
	//get first word length
	int wordlen = 0;
	while(str[wordlen] && !is_space(str[wordlen]))
	{
		wordlen++;
	}
	//fill word buffer starting from the end
	char *word = malloc(sizeof(char)*wordlen+1);
	if (!word)
		return 0;
	int i = wordlen;
	while(wordlen-1>=0)
	{
		word[wordlen-1] = str[wordlen-1]; 
		wordlen--;
	}
	word[i] = 0;
	//skip to second word
	str = str + i;
	while(is_space(*str))
		str++;
	int flag = 0;
	int end = 1;
	if (*str)
		end = 0;
	while(*str)
	{
		while(*str && !is_space(*str))
		{
			if(flag && is_space(*(str-1)))
				write(1, " ", 1);
			write(1, str, 1);
			str++;
			flag = 1;
		}
		while(*str && is_space(*str))
		{
			str++;
		}
	}
	if(!end)
		write(1, " ", 1);
	while(*word)
	{
		write(1, word, 1);
		word++;
	}
	write(1, "\n", 1);
}
