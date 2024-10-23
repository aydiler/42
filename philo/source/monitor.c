/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:47 by adiler            #+#    #+#             */
/*   Updated: 2024/10/23 15:46:45 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*monitor_routine(void *arg);
int		check_philosopher_death(t_resources *resources, int num_philos);
int		check_philosophers_finished(t_resources *resources, \
	int num_philos, int num_times_to_eat);
void	kill_philosophers(t_resources *resources, int num_philos);
int		refresh_last_time_ate(t_philo *philo);

void	*monitor_routine(void *arg)
{
	t_resources	*resources;
	int			num_philos;
	int			num_times_to_eat;

	resources = (t_resources *)arg;
	num_philos = resources->params.num_philos;
	num_times_to_eat = resources->params.num_times_to_eat;
	while (1)
	{
		if (check_philosopher_death(resources, num_philos))
		{
			return (NULL);
		}
		pthread_mutex_lock(&resources->print_mutex);
		if (num_times_to_eat != -1 && check_philosophers_finished \
			(resources, num_philos, num_times_to_eat))
		{
			pthread_mutex_unlock(&resources->print_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&resources->print_mutex);
	}
}

int	check_philosopher_death(t_resources *resources, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (refresh_last_time_ate(&resources->philos[i]))
		{
			print_status(&resources->philos[i], "died");
			kill_philosophers(resources, num_philos);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_philosophers_finished(t_resources *resources, int num_philos, \
	int num_times_to_eat)
{
	int	finished_philos;
	int	i;

	finished_philos = 0;
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_lock(&resources->eat_mutex);
		if (resources->philos[i].times_eaten >= num_times_to_eat)
			finished_philos++;
		pthread_mutex_unlock(&resources->eat_mutex);
		i++;
	}
	if (finished_philos == num_philos)
	{
		printf("All philosophers have eaten %d times\n", num_times_to_eat);
		kill_philosophers(resources, num_philos);
		return (1);
	}
	return (0);
}

void	kill_philosophers(t_resources *resources, int num_philos)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&resources->death_mutex);
	while (i < num_philos)
	{
		resources->philos[i].died = 1;
		i++;
	}
	pthread_mutex_unlock(&resources->death_mutex);
}

int	refresh_last_time_ate(t_philo *philo)
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
