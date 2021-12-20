#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>


typedef struct s_data
{
    int number_of_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
    long start_time;
} t_data;

typedef struct s_philo
{
    int number;
    long last_meal;
    t_data *data;
} t_philo;



int check_arguments(int argc, char **argv, t_data *data);
int	pos_number(char *str);
int	ft_atoi(const char *str);

#endif