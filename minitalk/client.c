#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        write(1, "Usage: ", 7);
        write(1, argv[0], sizeof(argv[0]));
        write(1, " <server_pid> <string_to_send>\n", 32);
        return 1;
    }

    int server_pid = atoi(argv[1]);
    char *string_to_send = argv[2];

    for (int i = 0; string_to_send[i] != '\0'; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (string_to_send[i] & (1 << j))
            {
                if (kill(server_pid, SIGUSR1) == -1)
                {
                    write(1, "Failed to send signal\n", 22);
                    return 1;
                }
            }
            else
            {
                if (kill(server_pid, SIGUSR2) == -1)
                {
                    write(1, "Failed to send signal\n", 22);
                    return 1;
                }
            }
            usleep(100);
        }
    }

    // Send null character to indicate end of message
    for (int j = 0; j < 8; j++)
    {
        if (kill(server_pid, SIGUSR2) == -1)
        {
            write(1, "Failed to send signal\n", 22);
            return 1;
        }
        usleep(100);
    }

    return 0;
}