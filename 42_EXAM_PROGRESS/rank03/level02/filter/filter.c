#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 2)
        return 1;

    char *target = argv[1];
	size_t target_len = strlen(target);
	char buffer[BUFFER_SIZE];

	ssize_t bytes_read;
	ssize_t target_length = (ssize_t)target_len;

	while ((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0)
	{
		ssize_t i = 0;
		if (bytes_read < target_length)
		{
			write(1, &buffer[i], bytes_read);
		}
		else
		{
			while (i <= bytes_read - target_length)
			{
				if (strncmp(&buffer[i], target, target_len) == 0)
				{
					int j = 0;
					while(j < target_len)
					{
						write(1, "*", 1);
						j++;
					}
					i += target_len;
				}
				else
				{
					write(1, &buffer[i], 1);
					i++;
				}
			}
			write(1, &buffer[i], bytes_read - i);
		}
	}
	
	return 0;	
}