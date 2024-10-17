#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>

#ifndef PHILO_H
#define PHILO_H

typedef struct s_philo {
    int id;
    struct s_fork *left_fork;
    struct s_fork *right_fork;
	time_t start_time;
	time_t last_meal;
    int* died;
} t_philo;

typedef struct s_fork {
    pthread_mutex_t mutex;
} t_fork;

#endif