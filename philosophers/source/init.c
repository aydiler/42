/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:36:11 by adiler            #+#    #+#             */
/*   Updated: 2024/10/21 16:38:33 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	parse_arguments(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> \
			<[number_of_times_each_philosopher_must_eat]>\n", argv[0]);
		return (0);
	}
	params->num_philos = atoi(argv[1]);
	if (params->num_philos < 1 || params->num_philos > MAX_PHILOSOPHERS)
	{
		printf("Number of philosophers must be between 1 and %d.\n", \
			MAX_PHILOSOPHERS);
		return (0);
	}
	params->time_to_die = atoi(argv[2]);
	params->time_to_eat = atoi(argv[3]);
	params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		params->num_times_to_eat = atoi(argv[5]);
	else
		params->num_times_to_eat = -1;
	return (1);
}

int	allocate_resources(t_resources *resources, int num_philos)
{
	resources->threads = malloc(sizeof(pthread_t) * (num_philos + 1));
	resources->philos = malloc(sizeof(t_philo) * num_philos);
	resources->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
	if (!resources->threads || !resources->philos || !resources->forks)
	{
		printf("Memory allocation failed\n");
		return (0);
	}
	return (1);
}

int	initialize_philos(t_resources *resources)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = resources->philos;
	while (i < resources->params.num_philos)
	{
		philo[i].id = i;
		philo[i].left_fork = &resources->forks[i];
		philo[i].right_fork = &resources->forks[(i + 1) % \
			resources->params.num_philos];
		philo[i].last_meal = resources->start_time;
		philo[i].times_eaten = 0;
		philo[i].died = 0;
		philo[i].params = resources->params;
		philo[i].start_time = resources->start_time;
		philo[i].print_mutex = &resources->print_mutex;
		philo[i].death_mutex = &resources->death_mutex;
		philo[i].eat_mutex = &resources->eat_mutex;
		i++;
	}
	return (TRUE);
}

int	initialize_mutexes(t_resources *resources, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&resources->forks[i], NULL) != 0)
		{
			printf("Mutex initialization failed\n");
			return (FALSE);
		}
		i++;
	}
	if (pthread_mutex_init(&resources->print_mutex, NULL) != 0 \
		|| pthread_mutex_init(&resources->death_mutex, NULL) != 0 \
		|| pthread_mutex_init(&resources->eat_mutex, NULL) != 0)
	{
		printf("Mutex initialization failed\n");
		return (FALSE);
	}
	return (TRUE);
}

int	initialize(t_resources *resources)
{
	if (!initialize_mutexes(resources, resources->params.num_philos))
	{
		free_resources_memory(resources);
		return (FALSE);
	}
	if (resources->params.num_times_to_eat == 0)
	{
		destroy_mutexes(resources, resources->params.num_philos);
		free_resources_memory(resources);
		return (TRUE);
	}
	resources->start_time = get_current_time();
	initialize_philos(resources);
	return (TRUE);
}