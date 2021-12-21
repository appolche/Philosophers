#include "philo.h"

void thinking(t_philo *phil)
{
    int time_to_think;

    time_to_think = phil->data->time_to_die - phil->data->time_to_sleep - phil->data->time_to_eat;
    printf("%lu ms | Philo #%d is thinking.\n", (get_time() - phil->data->start_time), phil->number + 1);
    usleep(time_to_think * 900);
}

void sleeping(t_philo *phil)
{
    printf("%lu ms | Philo #%d is sleeping.\n", (get_time() - phil->data->start_time), phil->number + 1);
    usleep(phil->data->time_to_sleep * 1000);
}

void eating(t_philo *phil)
{
    pthread_mutex_lock(phil->left_fork);
    printf("%lu ms | Philo #%d has taken a left_fork.\n", (get_time() - phil->data->start_time), phil->number + 1);
    pthread_mutex_lock(phil->right_fork);
    printf("%lu ms | Philo #%d has taken a right_fork.\n", (get_time() - phil->data->start_time), phil->number + 1);
    printf("%lu ms | Philo #%d is eating.\n", (get_time() - phil->data->start_time), phil->number + 1);
    usleep(phil->data->time_to_eat * 1000);
    pthread_mutex_unlock(phil->right_fork);
    pthread_mutex_unlock(phil->left_fork);
}

void *action(void *structure)
{
    t_philo *phil = (t_philo*)structure;
    while(1)
    {
        eating(phil);
        sleeping(phil);
        thinking(phil);
    }
    printf("SOS. I'm here!!!\n");
    //printf("%d\n", data->time_to_die);
    return (NULL);
}