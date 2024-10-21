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

int	check_terminated(t_philo *philo)
{
	pthread_mutex_lock(philo->death_mutex);
	if (philo->died)
	{
		pthread_mutex_unlock(philo->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->death_mutex);
	return (0);
}

void	print_status(t_philo *philo, const char *status)
{
	size_t	elapsed_time;

	pthread_mutex_lock(philo->print_mutex);
	elapsed_time = get_current_time() - philo->start_time;
	if (!check_terminated(philo))
	{
		printf("%zu %d %s\n", elapsed_time, philo->id + 1, status);
	}
	pthread_mutex_unlock(philo->print_mutex);
}

void	assign_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		philo->primary_fork = philo->left_fork;
		philo->secondary_fork = philo->right_fork;
	}
	else
	{
		philo->primary_fork = philo->right_fork;
		philo->secondary_fork = philo->left_fork;
	}
}

void	philo_eat(t_philo *philo)
{
	assign_forks(philo);

	pthread_mutex_lock(philo->primary_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->secondary_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_meal = get_current_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->params.time_to_eat, philo);
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(philo->secondary_fork);
	pthread_mutex_unlock(philo->primary_fork);
	ft_usleep(philo->params.time_to_sleep, philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->params.num_philos == 1)
	{
		print_status(philo, "has taken a fork");
		ft_usleep(philo->params.time_to_die, philo);
		return (NULL);
	}

	while (!check_terminated(philo))
	{
		philo_eat(philo);
		print_status(philo, "is thinking");
	}
	return (NULL);
}


int refresh_last_time_ate(t_philo *philo)
{
	size_t	current_time;
	size_t	time_to_die;

	current_time = get_current_time();
	time_to_die = philo->params.time_to_die;
	pthread_mutex_lock(philo->eat_mutex);
	if (current_time - philo->last_meal > time_to_die)
	{
		pthread_mutex_unlock(philo->eat_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->eat_mutex);
	return (0);
}

void *monitor_routine(void *arg)
{
	t_resources	*resources;
	int			num_philos;
	int			num_times_to_eat;
	int			finished_philos;
	int			i;
	int			j;

	resources = (t_resources *)arg;
	num_philos = resources->params.num_philos;
	num_times_to_eat = resources->params.num_times_to_eat;
	i = 0;
	while (1)
	{
		finished_philos = 0;
		i = 0;
		while (i < num_philos)
		{
			if (refresh_last_time_ate(&resources->philos[i]))
			{
				print_status(&resources->philos[i], "died");
				pthread_mutex_lock(&resources->death_mutex);
				j = 0;
				while (j < num_philos)
				{
					resources->philos[j].died = 1;
					j++;
				}
				pthread_mutex_unlock(&resources->death_mutex);
				return (NULL);
			}
			pthread_mutex_lock(&resources->eat_mutex);
			if (num_times_to_eat != -1 && \
				resources->philos[i].times_eaten >= num_times_to_eat)
			{
				pthread_mutex_unlock(&resources->eat_mutex);
				finished_philos++;
			}
			pthread_mutex_unlock(&resources->eat_mutex);
			i++;
		}
		if (num_times_to_eat != -1 && finished_philos == num_philos)
		{
			pthread_mutex_lock(&resources->death_mutex);
			printf("All philosophers have eaten %d times\n", num_times_to_eat);
			j = 0;
			while (j < num_philos)
			{
				resources->philos[j].died = 1;
				j++;
			}
			pthread_mutex_unlock(&resources->death_mutex);
			return (NULL);
		}

	}
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

int	initialize (t_resources *resources)
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

int threads(t_resources *resources)
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
