#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#define PHILOS 5

typedef struct s_philo {
    int id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *start_time_mutex;
    pthread_mutex_t *last_meal_mutex;
    pthread_mutex_t *died_mutex;
    time_t *start_time;
    time_t last_meal;
    int *died;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
} t_philo;

time_t get_time_in_ms(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void print_status(t_philo *philo, const char *status)
{
    time_t current_time = get_time_in_ms();
    time_t elapsed_time;
    
    pthread_mutex_lock(philo->start_time_mutex);
    elapsed_time = current_time - *philo->start_time;
    pthread_mutex_unlock(philo->start_time_mutex);
    printf("%ld %d %s\n", elapsed_time, philo->id + 1, status);
}

int check_death(t_philo *philo)
{
    int died;
    pthread_mutex_lock(philo->died_mutex);
    died = *philo->died;
    pthread_mutex_unlock(philo->died_mutex);
    return died;
}

void philo_sleep(time_t sleep_time, t_philo *philo)
{
    time_t wake_up = get_time_in_ms() + sleep_time;
    time_t current_time;
    time_t last_meal_time;

    while (get_time_in_ms() < wake_up)
    {
        if (check_death(philo))
            return;

        current_time = get_time_in_ms();
        pthread_mutex_lock(philo->last_meal_mutex);
        last_meal_time = philo->last_meal;
        pthread_mutex_unlock(philo->last_meal_mutex);

        if (current_time - last_meal_time > philo->time_to_die)
        {
            pthread_mutex_lock(philo->died_mutex);
            *philo->died = 1;
            pthread_mutex_unlock(philo->died_mutex);
            print_status(philo, "died");
            return;
        }
        usleep(200);
    }
}

void* philo_routine(void* philos)
{
    t_philo* philo = (t_philo*)philos;

    while (check_death(philo) == 0)
    {
        // Taking forks
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            if (check_death(philo)) { pthread_mutex_unlock(philo->left_fork); break; }
            print_status(philo, "has taken a fork");

            pthread_mutex_lock(philo->right_fork);
            if (check_death(philo)) { pthread_mutex_unlock(philo->right_fork); pthread_mutex_unlock(philo->left_fork); break; }
            print_status(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            if (check_death(philo)) { pthread_mutex_unlock(philo->right_fork); break; }
            print_status(philo, "has taken a fork");

            pthread_mutex_lock(philo->left_fork);
            if (check_death(philo)) { pthread_mutex_unlock(philo->left_fork); pthread_mutex_unlock(philo->right_fork); break; }
            print_status(philo, "has taken a fork");
        }

        // Eating
        if (check_death(philo)) { pthread_mutex_unlock(philo->left_fork); pthread_mutex_unlock(philo->right_fork); break; }
        print_status(philo, "is eating");

        pthread_mutex_lock(philo->last_meal_mutex);
        philo->last_meal = get_time_in_ms();
        pthread_mutex_unlock(philo->last_meal_mutex);

        philo_sleep(philo->time_to_eat, philo);

        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        if (check_death(philo))
            break;

        // Sleeping
        print_status(philo, "is sleeping");
        philo_sleep(philo->time_to_sleep, philo);

        if (check_death(philo))
            break;

        // Thinking
        print_status(philo, "is thinking");
    }

    return NULL;
}


void init_forks(pthread_mutex_t* forks, int number_of_philosophers)
{
    int i;

    i = 0;
    while(i < number_of_philosophers)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void init_philos(t_philo* philos, pthread_mutex_t* forks, time_t* start_time, int* died,
                 pthread_mutex_t* start_time_mutex, pthread_mutex_t* last_meal_mutex, pthread_mutex_t* died_mutex,
                 int number_of_philosophers, int time_to_die, int time_to_eat, int time_to_sleep)
{
    int i = 0;
    while (i < number_of_philosophers)
    {
        philos[i].id = i;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % number_of_philosophers];
        philos[i].start_time = start_time;
        philos[i].last_meal = *start_time;
        philos[i].died = died;
        philos[i].start_time_mutex = start_time_mutex;
        philos[i].last_meal_mutex = last_meal_mutex;
        philos[i].died_mutex = died_mutex;
        philos[i].number_of_philosophers = number_of_philosophers;
        philos[i].time_to_die = time_to_die;
        philos[i].time_to_eat = time_to_eat;
        philos[i].time_to_sleep = time_to_sleep;
        i++;
    }
}

void init_threads(pthread_t* th, t_philo* philos, int number_of_philosophers)
{
    int i;

    i = 0;
    while(i < number_of_philosophers)
    {
        if (pthread_create(&th[i], NULL, &philo_routine, &philos[i]) != 0)
            exit(1);
        i++;
    }
    i = 0;
    while(i < number_of_philosophers)
    {
        if (pthread_join(th[i], NULL) != 0)
            exit(1);
        i++;
    }
}

int main(int argc, char* argv[])
{
    if (argc != 5) {
        printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep>\n", argv[0]);
        return 1;
    }

    int number_of_philosophers = atoi(argv[1]);
    int time_to_die = atoi(argv[2]);
    int time_to_eat = atoi(argv[3]);
    int time_to_sleep = atoi(argv[4]);

    pthread_t* th = malloc(number_of_philosophers * sizeof(pthread_t));
    t_philo* philos = malloc(number_of_philosophers * sizeof(t_philo));
    pthread_mutex_t* forks = malloc(number_of_philosophers * sizeof(pthread_mutex_t));
    pthread_mutex_t start_time_mutex;
    pthread_mutex_t last_meal_mutex;
    pthread_mutex_t died_mutex;
    time_t start_time;
    int died = 0;

    pthread_mutex_init(&start_time_mutex, NULL);
    pthread_mutex_init(&last_meal_mutex, NULL);
    pthread_mutex_init(&died_mutex, NULL);

    start_time = get_time_in_ms();
    init_forks(forks, number_of_philosophers);
    init_philos(philos, forks, &start_time, &died, &start_time_mutex, &last_meal_mutex, &died_mutex,
                number_of_philosophers, time_to_die, time_to_eat, time_to_sleep);
    init_threads(th, philos, number_of_philosophers);

    pthread_mutex_destroy(&start_time_mutex);
    pthread_mutex_destroy(&last_meal_mutex);
    pthread_mutex_destroy(&died_mutex);

    free(th);
    free(philos);
    free(forks);

    return 0;
}