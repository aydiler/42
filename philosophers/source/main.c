#include "../includes/philo.h"
#include <sys/time.h>

#define PHILOS 5

void print_status(t_philo *philo, const char *status)
{
    struct timeval current_time;
    long long elapsed_us;

    gettimeofday(&current_time, NULL);
    elapsed_us = (current_time.tv_sec - philo->start_time.tv_sec) * 1000000LL + 
                 (current_time.tv_usec - philo->start_time.tv_usec);
    printf("%lld %d %s\n", elapsed_us / 1000, philo->id, status);
}

void* philo_routine(void* philos)
{
    t_philo* philo = (t_philo*)philos;

    while (1)
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(&philo->left_fork->mutex);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(&philo->right_fork->mutex);
            print_status(philo, "has taken a fork");
        }
        else
        {
            pthread_mutex_lock(&philo->right_fork->mutex);
            print_status(philo, "has taken a fork");
            pthread_mutex_lock(&philo->left_fork->mutex);
            print_status(philo, "has taken a fork");
        }

        print_status(philo, "is eating");
        usleep(200000);  // Sleep for 200ms (eating time)

        pthread_mutex_unlock(&philo->left_fork->mutex);
        pthread_mutex_unlock(&philo->right_fork->mutex);

        print_status(philo, "is sleeping");
        usleep(200000);  // Sleep for 200ms (sleeping time)

        print_status(philo, "is thinking");
        usleep(100000);  // Sleep for 100ms (thinking time)
    }

    return NULL;
}

void init_forks(t_fork* forks)
{
    int i;

    i = 0;
    while(i < PHILOS)
    {
        pthread_mutex_init(&forks[i].mutex, NULL);
        i++;
    }
}

void init_philos(t_philo* philos, t_fork* forks, struct timeval* start_time)
{
    int i;

    i = 0;
    while(i < PHILOS)
    {
        philos[i].id = i;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % PHILOS];
        philos[i].start_time = *start_time;
        i++;
    }
}

void init_threads(pthread_t* th, t_philo* philos, t_fork* forks)
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
    t_fork forks[PHILOS];
    struct timeval start_time;

    gettimeofday(&start_time, NULL);
    init_forks(forks);
    init_philos(philos, forks, &start_time);
    init_threads(th, philos, forks);

    return 0;
}