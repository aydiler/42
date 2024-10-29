#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main()
{
	char buffer[BUFFER_SIZE];

	size_t read_size = read(0, buffer, BUFFER_SIZE);
	buffer[read_size] = '\0';
	write(1, buffer, read_size);
	return 0;
}
	