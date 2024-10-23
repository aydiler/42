/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:47 by adiler            #+#    #+#             */
/*   Updated: 2024/10/21 18:32:40 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_status(t_philo *philo, const char *status)
{
	size_t	elapsed_time;

	pthread_mutex_lock(philo->print_mutex);
	elapsed_time = get_current_time() - philo->start_time;
	if (!check_terminated(philo))
	{
		printf("%zu %d %s\n", elapsed_time, philo->id, status);
	}
	pthread_mutex_unlock(philo->print_mutex);
}

void	destroy_mutexes(t_resources *resources, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&resources->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&resources->print_mutex);
	pthread_mutex_destroy(&resources->death_mutex);
	pthread_mutex_destroy(&resources->eat_mutex);
}

void	free_resources_memory(t_resources *resources)
{
	free(resources->threads);
	free(resources->philos);
	free(resources->forks);
}

int	threads(t_resources *resources)
{
	if (!create_threads(resources))
	{
		destroy_mutexes(resources, resources->params.num_philos);
		free_resources_memory(resources);
		return (FALSE);
	}
	if (!join_threads(resources))
	{
		destroy_mutexes(resources, resources->params.num_philos);
		free_resources_memory(resources);
		return (FALSE);
	}
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_resources	resources;

	if (!parse_arguments(argc, argv, &resources.params))
		return (1);
	if (!allocate_resources(&resources, resources.params.num_philos))
		return (1);
	if (!initialize(&resources))
	{
		destroy_mutexes(&resources, resources.params.num_philos);
		free_resources_memory(&resources);
		return (1);
	}
	if (!threads(&resources))
	{
		destroy_mutexes(&resources, resources.params.num_philos);
		free_resources_memory(&resources);
		return (1);
	}
	destroy_mutexes(&resources, resources.params.num_philos);
	free_resources_memory(&resources);
	return (0);
}
