/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:40:44 by adiler            #+#    #+#             */
/*   Updated: 2024/10/21 16:42:49 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t sleep_time, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < sleep_time)
	{
		if (check_terminated(philo))
			return (1);
		usleep(USLEEP_INTERVAL);
	}
	return (0);
}
