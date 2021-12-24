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
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    int must_eat_count;
    long start_time;
    pthread_mutex_t print_mutex;
} t_data;

typedef struct s_philo
{
    int number;
    int meal_counter;
    long last_meal;
    pthread_mutex_t *right_fork;
    pthread_mutex_t *left_fork;
    t_data *data;
} t_philo;

pthread_mutex_t *fork_parsing(t_data *data, pthread_mutex_t *fork);
int simulation (t_data *data);
void *action(void *structure);
void thinking(t_philo *phil);
void sleeping(t_philo *phil);
void eating(t_philo *phil);
long   get_time(void);
int check_arguments(int argc, char **argv, t_data *data);
int	pos_number(char *str);
int	ft_atoi(const char *str);

#endif