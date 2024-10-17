#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

/*
** Constants
*/
#define MAX_PHILOSOPHERS 200
#define USLEEP_INTERVAL 200
#define TRUE 1
#define FALSE 0

/*
** Structures
*/
typedef struct s_philo
{
    int             id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    long long       last_meal;
    struct s_resources *resources;  // Pointer to the shared resources
} t_philo;

typedef struct s_params
{
    int num_philos;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int num_times_to_eat;
} t_params;

typedef struct s_resources
{
    pthread_t       *threads;
    t_philo         *philos;
    pthread_mutex_t *forks;
    pthread_mutex_t start_time_mutex;
    pthread_mutex_t died_mutex;
    pthread_mutex_t times_eaten_mutex;
    long long       start_time;
    int             died;
    int             times_eaten;
    t_params        params;  // Include params in resources for easy access
} t_resources;

long long get_time_in_ms(void)
{
    struct timeval tv;
    long long time_in_ms;

    gettimeofday(&tv, NULL);
    time_in_ms = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time_in_ms);
}

void print_status(t_philo *philo, const char *status)
{
    long long current_time;
    long long elapsed_time;

    current_time = get_time_in_ms();

    pthread_mutex_lock(&philo->resources->start_time_mutex);
    elapsed_time = current_time - philo->resources->start_time;
    pthread_mutex_unlock(&philo->resources->start_time_mutex);

    pthread_mutex_lock(&philo->resources->died_mutex);
	printf("%lld %d %s\n", elapsed_time, philo->id + 1, status);
    pthread_mutex_unlock(&philo->resources->died_mutex);
}

void refresh_last_time_ate(t_philo *philo)
{
    long long current_time = get_time_in_ms();
    long long last_meal_time;
    long long time_to_die;

    pthread_mutex_lock(&philo->resources->died_mutex);
    if (philo->resources->died)
    {
        pthread_mutex_unlock(&philo->resources->died_mutex);
        return;
    }

    last_meal_time = philo->last_meal;
    time_to_die = philo->resources->params.time_to_die;
    if (current_time - last_meal_time > time_to_die)
    {
        philo->resources->died = 1;
        pthread_mutex_unlock(&philo->resources->died_mutex);
        print_status(philo, "died");
    }
    else
    {
        pthread_mutex_unlock(&philo->resources->died_mutex);
    }
}

void refresh_times_eaten(t_philo *philo)
{
    int times_eaten;
    int num_times_to_eat;

    pthread_mutex_lock(&philo->resources->died_mutex);
    if (philo->resources->died)
    {
        pthread_mutex_unlock(&philo->resources->died_mutex);
        return;
    }

    pthread_mutex_lock(&philo->resources->times_eaten_mutex);
    times_eaten = philo->resources->times_eaten;
    pthread_mutex_unlock(&philo->resources->times_eaten_mutex);
    
    num_times_to_eat = philo->resources->params.num_times_to_eat;
    if (num_times_to_eat != -1 && times_eaten >= num_times_to_eat)
    {
        philo->resources->died = 1;
        pthread_mutex_unlock(&philo->resources->died_mutex);
        print_status(philo, "has eaten enough");
    }
    else
    {
        pthread_mutex_unlock(&philo->resources->died_mutex);
    }
}

int check_terminated(t_philo *philo)
{
    int terminated = 0;

    pthread_mutex_lock(&philo->resources->died_mutex);
    terminated = philo->resources->died;
    pthread_mutex_unlock(&philo->resources->died_mutex);

    if (!terminated)
    {
        refresh_last_time_ate(philo);
        refresh_times_eaten(philo);

        pthread_mutex_lock(&philo->resources->died_mutex);
        terminated = philo->resources->died;
        pthread_mutex_unlock(&philo->resources->died_mutex);
    }

    return terminated;
}

int philo_sleep(long long sleep_time, t_philo *philo)
{
    long long wake_up;

    wake_up = get_time_in_ms() + sleep_time;
    while (get_time_in_ms() < wake_up)
    {
        if (check_terminated(philo))
            return (1);
        usleep(USLEEP_INTERVAL);
    }
    return (0);
}

void *philo_routine(void *philos)
{
    t_philo *philo;

    philo = (t_philo *)philos;
    while (1)
    {
        if (check_terminated(philo))
            return NULL;

        // Try to take forks
        pthread_mutex_lock(philo->left_fork);
        if (check_terminated(philo))
        {
            pthread_mutex_unlock(philo->left_fork);
            return NULL;
        }
        print_status(philo, "has taken a fork");

        pthread_mutex_lock(philo->right_fork);
        if (check_terminated(philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return NULL;
        }
        print_status(philo, "has taken a fork");

        // Eating
        if (check_terminated(philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return NULL;
        }
        print_status(philo, "is eating");
        philo->last_meal = get_time_in_ms();
        pthread_mutex_lock(&philo->resources->times_eaten_mutex);
        philo->resources->times_eaten++;
        pthread_mutex_unlock(&philo->resources->times_eaten_mutex);

        if (philo_sleep(philo->resources->params.time_to_eat, philo))
        {
            pthread_mutex_unlock(philo->right_fork);
            pthread_mutex_unlock(philo->left_fork);
            return NULL;
        }

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Sleeping
        if (check_terminated(philo))
            return NULL;
        print_status(philo, "is sleeping");
        if (philo_sleep(philo->resources->params.time_to_sleep, philo))
            return NULL;

        // Thinking
        if (check_terminated(philo))
            return NULL;
        print_status(philo, "is thinking");
    }
    return NULL;
}

void	init_forks(pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Mutex initialization failed\n");
			exit(1);
		}
		i++;
	}
}

void	init_threads(pthread_t *threads, t_philo *philos,
				int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		if (pthread_create(&threads[i], NULL, &philo_routine,
				&philos[i]) != 0)
		{
			printf("Thread creation failed\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			printf("Thread join failed\n");
			exit(1);
		}
		i++;
	}
}

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

void free_resources(t_resources *resources)
{
    free(resources->threads);
    free(resources->philos);
    free(resources->forks);
}

int allocate_resources(t_resources *resources, int num_philos)
{
    resources->threads = malloc(sizeof(pthread_t) * num_philos);
    resources->philos = malloc(sizeof(t_philo) * num_philos);
    resources->forks = malloc(sizeof(pthread_mutex_t) * num_philos);
    if (!resources->threads || !resources->philos || !resources->forks)
    {
        printf("Memory allocation failed\n");
        free_resources(resources);
        return FALSE;
    }
    return TRUE;
}

int initialize_mutexes(t_resources *resources, t_params *params)
{
    if (pthread_mutex_init(&resources->start_time_mutex, NULL) != 0 ||
        pthread_mutex_init(&resources->died_mutex, NULL) != 0 ||
        pthread_mutex_init(&resources->times_eaten_mutex, NULL) != 0)
    {
        printf("Mutex initialization failed\n");
        return FALSE;
    }
    init_forks(resources->forks, params->num_philos);
    return TRUE;
}

void init_philo(t_philo *philo, t_resources *resources, int id)
{
    philo->id = id;
    philo->left_fork = &resources->forks[id];
    philo->right_fork = &resources->forks[(id + 1) % resources->params.num_philos];
    philo->last_meal = resources->start_time;
    philo->resources = resources;
}

void init_philos(t_philo *philos, t_resources *resources)
{
    int i;

    i = 0;
    while (i < resources->params.num_philos)
    {
        init_philo(&philos[i], resources, i);
        i++;
    }
}

void initialize_simulation(t_resources *resources, t_params *params)
{
    resources->start_time = get_time_in_ms();
    resources->died = 0;
    resources->times_eaten = 0;
    resources->params = *params;  // Copy params into resources

    init_philos(resources->philos, resources);
}

void cleanup_simulation(t_resources *resources, int num_philos)
{
    pthread_mutex_destroy(&resources->start_time_mutex);
    pthread_mutex_destroy(&resources->died_mutex);
    pthread_mutex_destroy(&resources->times_eaten_mutex);

    for (int i = 0; i < num_philos; i++)
    {
        pthread_mutex_destroy(&resources->forks[i]);
    }

    free_resources(resources);
}

int main(int argc, char **argv)
{
    t_params params;
    t_resources resources;

    if (!parse_arguments(argc, argv, &params))
        return 1;
    if (!allocate_resources(&resources, params.num_philos))
        return 1;
    if (!initialize_mutexes(&resources, &params))
    {
        free_resources(&resources);
        return 1;
    }
    initialize_simulation(&resources, &params);
    init_threads(resources.threads, resources.philos, params.num_philos);
    cleanup_simulation(&resources, params.num_philos);
    return 0;
}