#define _GNU_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	char *needle = argv[1];
	size_t needle_len = strlen(needle);
	if (needle_len == 0)
		return 1;
	char *input_buff = NULL;
	size_t total = 0;
	char *temp_buff[10];

	int bytes_read;
	while((bytes_read = read(0, temp_buff, sizeof(temp_buff))) > 0)
	{
		char *new_buff = realloc(input_buff, total + bytes_read);
		if(!new_buff)
		{
			fprintf(stderr, "Error: ");
			free(input_buff);
			return 1;
		}
		input_buff = new_buff;
		memmove(input_buff + total, temp_buff, bytes_read);
		total += bytes_read;
	}
	if(bytes_read < 0)
	{
		fprintf(stderr, "Error: ");
		free(input_buff);
		return 1;
	}
	//printf("%s", input_buff);
	char *current_pos = input_buff;
	size_t remaining = total;
	while((current_pos = memmem(current_pos, remaining, needle, needle_len)))
	{
		size_t i = 0;
		while(i < needle_len)
		{
			current_pos[i] = '*';
			i++;
		}
		current_pos += needle_len;
		remaining = total - (current_pos - input_buff);
	}
	int written = write(1, input_buff, total);
	if (written < 0)
	{
		free(input_buff);
		return 1;
	}
	free(input_buff);
	return 0;
}
