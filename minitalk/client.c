/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:00:43 by adiler            #+#    #+#             */
/*   Updated: 2024/09/06 18:33:18 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int	send_signal(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		write(1, "Failed to send signal\n", 22);
		return (1);
	}
	return (0);
}

int	send_char(int server_pid, char c)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		if (c & (1 << j))
		{
			if (send_signal(server_pid, SIGUSR1))
				return (1);
		}
		else
		{
			if (send_signal(server_pid, SIGUSR2))
				return (1);
		}
		usleep(100);
		j++;
	}
	return (0);
}

int	send_string(int server_pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (send_char(server_pid, str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	send_null_terminator(int server_pid)
{
	int	j;

	j = 0;
	while (j < 8)
	{
		if (send_signal(server_pid, SIGUSR2))
			return (1);
		usleep(100);
		j++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int		server_pid;
	char	*program_name;

	if (argc != 3)
	{
		program_name = argv[0];
		write(1, "Usage: ", 7);
		write(1, program_name, sizeof(program_name));
		write(1, "<server_pid> <string_to_send>\n", 32);
		return (1);
	}
	server_pid = atoi(argv[1]);
	if (send_string(server_pid, argv[2]))
		return (1);
	if (send_null_terminator(server_pid))
		return (1);
	return (0);
}
