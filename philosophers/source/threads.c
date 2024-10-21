/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:34:14 by adiler            #+#    #+#             */
/*   Updated: 2024/10/21 16:35:52 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_resources *resources)
{
	int	i;

	i = 0;
	while (i < resources->params.num_philos)
	{
		if (pthread_create(&resources->threads[i], NULL, &philo_routine, \
			&resources->philos[i]) != 0)
		{
			printf("Thread creation failed for philosopher %d\n", i + 1);
			return (0);
		}
		i++;
	}
	if (pthread_create(&resources->monitor_thread, NULL, &monitor_routine, \
		resources) != 0)
	{
		printf("Monitor thread creation failed\n");
		return (0);
	}
	return (1);
}

int	join_threads(t_resources *resources)
{
	int	i;

	i = 0;
	while (i < resources->params.num_philos)
	{
		if (pthread_join(resources->threads[i], NULL) != 0)
		{
			printf("Thread join failed for philosopher %d\n", i + 1);
			return (0);
		}
		i++;
	}
	if (pthread_join(resources->monitor_thread, NULL) != 0)
	{
		printf("Monitor thread join failed\n");
		return (0);
	}

	return (1);
}