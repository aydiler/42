#include "../includes/philo.h"

/*
** Utility Functions
*/

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int check_terminated(t_philo *philo)
{
    pthread_mutex_lock(philo->death_mutex);
    if (philo->died)
    {
        pthread_mutex_unlock(philo->death_mutex);
        return 1;
    }
    pthread_mutex_unlock(philo->death_mutex);
    return 0;
}

void print_status(t_philo *philo, const char *status)
{
    size_t elapsed_time;

    pthread_mutex_lock(philo->print_mutex);
    elapsed_time = get_current_time() - philo->start_time;
    if (!check_terminated(philo))
    {
        printf("%zu %d %s\n", elapsed_time, philo->id + 1, status);
    }
    pthread_mutex_unlock(philo->print_mutex);
}

int ft_usleep(size_t sleep_time, t_philo *philo)
{
	size_t  start;

	start = get_current_time();
	while ((get_current_time() - start) < sleep_time)
    {
        if (check_terminated(philo))
            return (1);
        usleep(USLEEP_INTERVAL);
    }
	return (0);
}

void eat_and_sleep(t_philo *philo)
{
    pthread_mutex_t *primary_fork;
    pthread_mutex_t *secondary_fork;

    // Determine which forks to pick up first
    if (philo->id % 2 == 0)
    {
        primary_fork = philo->left_fork;
        secondary_fork = philo->right_fork;
    } 
    else
    {
        primary_fork = philo->right_fork;
        secondary_fork = philo->left_fork;
    }

    // Acquire forks
    pthread_mutex_lock(primary_fork);
    if(check_terminated(philo))
    {
        pthread_mutex_unlock(primary_fork);
        return;
    }
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(secondary_fork);
    print_status(philo, "has taken a fork");

    // Start eating
    print_status(philo, "is eating");

    // Update eating stats
    pthread_mutex_lock(philo->eat_mutex);
    philo->last_meal = get_current_time();
    philo->times_eaten++;
    pthread_mutex_unlock(philo->eat_mutex);

    // Simulate eating
    ft_usleep(philo->params.time_to_eat, philo);

    // Check for termination before proceeding
    if(check_terminated(philo))
    {
        pthread_mutex_unlock(secondary_fork);
        pthread_mutex_unlock(primary_fork);
        return;
    }

    // Print "is sleeping" before releasing forks
    print_status(philo, "is sleeping");

    // Release forks after printing "is sleeping"
    pthread_mutex_unlock(secondary_fork);
    pthread_mutex_unlock(primary_fork);

    // Simulate sleeping
    ft_usleep(philo->params.time_to_sleep, philo);
}


void philo_sleep(t_philo *philo)
{
    if(check_terminated(philo))
    {
        return;
    }
    print_status(philo, "is sleeping");
    ft_usleep(philo->params.time_to_sleep, philo);
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->params.num_philos == 1)
    {
        print_status(philo, "has taken a fork");
        ft_usleep(philo->params.time_to_die, philo);
        return NULL;
    }

    while (!check_terminated(philo))
    {
        eat_and_sleep(philo);
        print_status(philo, "is thinking");
    }
    return NULL;
}


int refresh_last_time_ate(t_philo *philo)
{
    size_t current_time = get_current_time();
    size_t time_to_die = philo->params.time_to_die;

    pthread_mutex_lock(philo->eat_mutex);
    if (current_time - philo->last_meal > time_to_die)
    {
        pthread_mutex_unlock(philo->eat_mutex);
        return 1;
    }
    pthread_mutex_unlock(philo->eat_mutex);
    return 0;
}

void *monitor_routine(void *arg)
{
    t_resources *resources = (t_resources *)arg;
    int num_philos = resources->params.num_philos;
    int num_times_to_eat = resources->params.num_times_to_eat;
    int finished_philos;
    int i;

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
                for (int j = 0; j < num_philos; j++)
                {
                    resources->philos[j].died = 1;
                }
                pthread_mutex_unlock(&resources->death_mutex);
                return NULL;
            }

            // Check if all philosophers have eaten enough times
            pthread_mutex_lock(&resources->eat_mutex);
            if (num_times_to_eat != -1 && resources->philos[i].times_eaten >= num_times_to_eat)
            {
                pthread_mutex_unlock(&resources->eat_mutex);
                finished_philos++;
            }
            pthread_mutex_unlock(&resources->eat_mutex);
            i++;
        }

        // If all philosophers have eaten enough times, terminate the simulation
        if (num_times_to_eat != -1 && finished_philos == num_philos)
        {
            pthread_mutex_lock(&resources->death_mutex);
            printf("All philosophers have eaten %d times\n", num_times_to_eat);
            for (int i = 0; i < num_philos; i++)
            {
                resources->philos[i].died = 1;
            }
            pthread_mutex_unlock(&resources->death_mutex);
            return NULL;
        }

    }
}

int initialize_mutexes(t_resources *resources, int num_philos)
{
    for (int i = 0; i < num_philos; i++)
    {
        if (pthread_mutex_init(&resources->forks[i], NULL) != 0)
        {
            printf("Mutex initialization failed\n");
            return FALSE;
        }
    }
    if (pthread_mutex_init(&resources->print_mutex, NULL) != 0)
    {
        printf("Mutex initialization failed\n");
        return FALSE;
    }
    if (pthread_mutex_init(&resources->death_mutex, NULL) != 0)
    {
        printf("Mutex initialization failed\n");
        return FALSE;
    }
    if (pthread_mutex_init(&resources->eat_mutex, NULL) != 0)
    {
        printf("Mutex initialization failed\n");
        return FALSE;
    }
    return TRUE;
}

int initialize_philos(t_resources *resources)
{
    t_philo *philo = resources->philos;

    for (int i = 0; i < resources->params.num_philos; i++)
    {
        philo[i].id = i;
        philo[i].left_fork = &resources->forks[i];
        philo[i].right_fork = &resources->forks[(i + 1) % resources->params.num_philos];
        philo[i].last_meal = resources->start_time;
        philo[i].times_eaten = 0;
        philo[i].died = 0;
        philo[i].params = resources->params;
        philo[i].start_time = resources->start_time;
        philo[i].print_mutex = &resources->print_mutex;
        philo[i].death_mutex = &resources->death_mutex;
        philo[i].eat_mutex = &resources->eat_mutex;
    }
    return TRUE;
}

void destroy_mutexes(t_resources *resources, int num_philos)
{
    for (int i = 0; i < num_philos; i++)
    {
        pthread_mutex_destroy(&resources->forks[i]);
    }
    pthread_mutex_destroy(&resources->print_mutex);
    pthread_mutex_destroy(&resources->death_mutex);
    pthread_mutex_destroy(&resources->eat_mutex);
}

void free_resources_memory(t_resources *resources)
{
    free(resources->threads);
    free(resources->philos);
    free(resources->forks);
}

int main(int argc, char **argv)
{
    t_resources resources;

    // Initialize resources
    if (!parse_arguments(argc, argv, &resources.params))
        return 1;
    if (!allocate_resources(&resources, resources.params.num_philos))
        return 1;
    if (!initialize_mutexes(&resources, resources.params.num_philos))
    {
        free_resources_memory(&resources);
        return 1;
    }

    if (resources.params.num_times_to_eat == 0)
    {
        free_resources_memory(&resources);
        return 0;
    }

    // Initialize start time
    resources.start_time = get_current_time();

    // Initialize philosophers
    initialize_philos(&resources);

    // Create philosopher and monitor threads
    if (!create_threads(&resources))
    {
        destroy_mutexes(&resources, resources.params.num_philos);
        free_resources_memory(&resources);
        return 1;
    }

    // Join all threads
    if (!join_threads(&resources))
    {
        destroy_mutexes(&resources, resources.params.num_philos);
        free_resources_memory(&resources);
        return 1;
    }
    // Cleanup
    destroy_mutexes(&resources, resources.params.num_philos);
    free_resources_memory(&resources);

    return 0;
}
