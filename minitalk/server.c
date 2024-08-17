#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_MESSAGE_LENGTH 1024

static char message[MAX_MESSAGE_LENGTH];
static volatile int message_length = 0;

void sigusr_handler(int signum)
{
    static int bit_count = 0;
    static int current_char = 0;

    if (signum == SIGUSR1)
        current_char |= (1 << bit_count);

    bit_count++;

    if (bit_count == 8)
    {
        message[message_length++] = current_char;

        if (current_char == '\0' || message_length == MAX_MESSAGE_LENGTH)
        {
            write(1, message, message_length - 1);
            write(1, "\n", 1);
            message_length = 0;
            message[0] = '\0';
        }

        bit_count = 0;
        current_char = 0;
    }
}

int main()
{
    struct sigaction sa;

    write(1, "Server PID: ", 12);
    char pid_str[10];
    pid_str[0] = '\0';
    char *pid_ptr = pid_str;
    int pid = getpid();
    while (pid != 0)
    {
        *pid_ptr++ = '0' + (pid % 10);
        pid /= 10;
    }
    *pid_ptr = '\0';
    int len = pid_ptr - pid_str;
    for (int i = 0; i < len / 2; i++)
    {
        char temp = pid_str[i];
        pid_str[i] = pid_str[len - 1 - i];
        pid_str[len - 1 - i] = temp;
    }
    write(1, pid_str, len);
    write(1, "\n", 1);

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = sigusr_handler;
    sa.sa_flags = 0;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    while (1)
        pause();

    return 0;
}