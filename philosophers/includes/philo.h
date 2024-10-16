#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#ifndef PHILO_H
#define PHILO_H

typedef struct s_shared_data {
    struct timeval start_time;
    pthread_mutex_t time_mutex;
} t_shared_data;

typedef struct s_philo {
    int id;
	t_shared_data *shared_data;
    pthread_mutex_t *print_mutex;
    struct s_fork *left_fork;
    struct s_fork *right_fork;
    struct timeval start_time;
} t_philo;

typedef struct s_fork {
    pthread_mutex_t mutex;
} t_fork;

#endif