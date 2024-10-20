#include "../includes/philo.h"

int parse_arguments(int argc, char **argv, t_params *params)
{
    if (argc != 5 && argc != 6)
    {
        printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <[number_of_times_each_philosopher_must_eat]>\n", argv[0]);
        return FALSE;
    }
    params->num_philos = atoi(argv[1]);
    if (params->num_philos < 1 || params->num_philos > MAX_PHILOSOPHERS)
    {
        printf("Number of philosophers must be between 1 and %d.\n", MAX_PHILOSOPHERS);
        return FALSE;
    }
    params->time_to_die = atoi(argv[2]);
    params->time_to_eat = atoi(argv[3]);
    params->time_to_sleep = atoi(argv[4]);
    if (argc == 6)
        params->num_times_to_eat = atoi(argv[5]);
    else
        params->num_times_to_eat = -1;
    return TRUE;
}

int allocate_resources(t_resources *resources, int num_philos)
{
    resources->threads = malloc(sizeof(pthread_t) * (num_philos + 1));
    resources->philos = malloc(sizeof(t_philo) * num_philos);
    resources->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!resources->threads || !resources->philos || !resources->forks)
    {
        printf("Memory allocation failed\n");
        return FALSE;
    }
    return TRUE;
}