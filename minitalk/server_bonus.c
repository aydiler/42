/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:25:40 by adiler            #+#    #+#             */
/*   Updated: 2024/09/12 18:39:58 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include "./includes/libft/libft.h"

#define MAX_MESSAGE_LENGTH 1024

static void	sigusr_handler(int signum, siginfo_t *info, void *context)
{
	static char	message[MAX_MESSAGE_LENGTH];
	static int	bit_count;
	static int	char_index;
	static int	current_char;

	(void)context;
	if (signum == SIGUSR1)
		current_char |= (1 << bit_count);
	else if (signum == SIGUSR2)
		current_char &= ~(1 << bit_count);
	if (++bit_count == 8)
	{
		message[char_index] = current_char;
		char_index++;
		if (current_char == '\0' || char_index == MAX_MESSAGE_LENGTH - 1)
		{
			message[char_index] = '\0';
			write(1, message, char_index);
			write(1, "\n", 1);
			char_index = 0;
			kill(info->si_pid, SIGUSR1);
		}
		bit_count = 0;
		current_char = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	write(1, "Server PID: ", 12);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sigusr_handler;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
