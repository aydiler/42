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
    time_t start_time;
    time_t last_meal;
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
    time_t elapsed_time = current_time - philo->start_time;
    printf("%ld %d %s\n", elapsed_time, philo->id + 1, status);
}

void philo_sleep(time_t sleep_time, t_philo *philo)
{
    time_t wake_up = get_time_in_ms() + sleep_time;
    while (get_time_in_ms() < wake_up)
    {
        if (get_time_in_ms() - philo->last_meal > 300)
        {
            print_status(philo, "died");
            exit(1);
        }
        usleep(10);
    }
}

void* philo_routine(void* philos)
{
    t_philo* philo = (t_philo*)philos;

    while (1)
    {
        // Taking forks
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(philo->right_fork);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(philo->left_fork);
            print_status(philo, "has taken a fork");
        }

        // Eating
        print_status(philo, "is eating");
        philo->last_meal = get_time_in_ms();
        philo_sleep(100, philo);  // Sleep for 70ms (eating time)

        // Release forks
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);

        // Sleeping
        print_status(philo, "is sleeping");
        philo_sleep(200, philo);  // Sleep for 80ms (sleeping time)

        // Thinking
        print_status(philo, "is thinking");
        philo_sleep(200, philo);  // Sleep for 110ms (thinking time)
    }

    return NULL;
}

void init_forks(pthread_mutex_t* forks)
{
    int i;

    i = 0;
    while(i < PHILOS)
    {
        pthread_mutex_init(&forks[i], NULL);
        i++;
    }
}

void init_philos(t_philo* philos, pthread_mutex_t* forks, time_t start_time)
{
    int i = 0;
    while (i < PHILOS)
    {
        philos[i].id = i;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % PHILOS];
        philos[i].start_time = start_time;
        philos[i].last_meal = start_time;
        i++;
    }
}

void init_threads(pthread_t* th, t_philo* philos)
{
    int i;

    i = 0;
    while(i < PHILOS)
    {
        if (pthread_create(&th[i], NULL, &philo_routine, &philos[i]) != 0)
            exit(1);
        i++;
    }
    i = 0;
    while(i < PHILOS)
    {
        if (pthread_join(th[i], NULL) != 0)
            exit(1);
        i++;
    }
}

int main(int argc, char* argv[])
{
    pthread_t th[PHILOS];
    t_philo philos[PHILOS];
    pthread_mutex_t forks[PHILOS];
    time_t start_time;

    start_time = get_time_in_ms();
    init_forks(forks);
    init_philos(philos, forks, start_time);
    init_threads(th, philos);

    return 0;
}