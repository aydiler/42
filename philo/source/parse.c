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

static int	validate_time_params(int time_to_die, \
	int time_to_eat, int time_to_sleep)
{
	if (time_to_die <= 0 || time_to_eat <= 0 || time_to_sleep <= 0)
	{
		printf("Time values must be positive.\n");
		return (0);
	}
	return (1);
}

static int	validate_philo_params(int num_philos)
{
	if (num_philos < 1 || num_philos > MAX_PHILOSOPHERS)
	{
		printf("Number of philosophers must be between 1 and %d.\n", \
			MAX_PHILOSOPHERS);
		return (0);
	}
	return (1);
}

static int	parse_time_params(int argc, char **argv, t_params *params)
{
	params->time_to_die = atoi(argv[2]);
	params->time_to_eat = atoi(argv[3]);
	params->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
	{
		if (atoi(argv[5]) <= 0)
		{
			printf("Invalid number of times to eat.\n");
			return (0);
		}
		params->num_times_to_eat = atoi(argv[5]);
	}
	else
		params->num_times_to_eat = -1;
	return (validate_time_params(params->time_to_die, \
		params->time_to_eat, params->time_to_sleep));
}

static int	parse_philo_params(char **argv, t_params *params)
{
	params->num_philos = atoi(argv[1]);
	return (validate_philo_params(params->num_philos));
}

int	parse_arguments(int argc, char **argv, t_params *params)
{
	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> \
			<time_to_sleep> <[number_of_times_each_philosopher_must_eat]>\n", \
			argv[0]);
		return (0);
	}
	if (!parse_philo_params(argv, params))
		return (0);
	if (!parse_time_params(argc, argv, params))
		return (0);
	return (1);
}
