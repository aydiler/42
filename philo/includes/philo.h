/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adiler <adiler@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:45:59 by adiler            #+#    #+#             */
/*   Updated: 2024/10/21 16:58:00 by adiler           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <stdint.h>

#define MAX_PHILOSOPHERS 200
#define USLEEP_INTERVAL 200
#define TRUE 1
#define FALSE 0

typedef struct s_params
{
	int	num_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_times_to_eat;
}	t_params;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*primary_fork;
	pthread_mutex_t	*secondary_fork;
	size_t			last_meal;
	int				times_eaten;
	int				died;
	t_params		params;
	size_t			start_time;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*eat_mutex;
}	t_philo;

typedef struct s_resources
{
	pthread_t		*threads;
	pthread_t		monitor_thread;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	long long		start_time;
	t_params		params;
	int				died;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	sleep_mutex;
}	t_resources;

typedef struct s_thread_arg
{
	t_philo	*philo;
}	t_thread_arg;

int		parse_arguments(int argc, char **argv, t_params *params);
int		allocate_resources(t_resources *resources, int num_philos);
int		initialize_mutexes(t_resources *resources, int num_philos);
int		initialize_philos(t_resources *resources);
int		create_threads(t_resources *resources);
int		join_threads(t_resources *resources);
void	destroy_mutexes(t_resources *resources, int num_philos);
void	free_resources_memory(t_resources *resources);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	print_status(t_philo *philo, const char *status);
int		check_terminated(t_philo *philo);
int		refresh_last_time_ate(t_philo *philo);
size_t	get_current_time(void);
int		ft_usleep(size_t sleep_time, t_philo *philo);
int		initialize(t_resources *resources);