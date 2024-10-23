/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:38:47 by adiler            #+#    #+#             */
/*   Updated: 2024/10/23 17:23:23 by adiler           ###   ########.fr       */
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

void	philo_eat(t_philo *philo)
{
	if (check_terminated(philo))
		return ;
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_meal = get_current_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	if (ft_usleep(philo->params.time_to_eat, philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	print_status(philo, "is sleeping");
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	if (ft_usleep(philo->params.time_to_sleep, philo))
		return ;
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
	if (philo->id % 2 == 0)
		usleep(100);
	while (!check_terminated(philo))
	{
		philo_eat(philo);
		if (check_terminated(philo))
			return (NULL);
		print_status(philo, "is thinking");
	}
	return (NULL);
}
