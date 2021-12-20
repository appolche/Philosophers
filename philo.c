#include "philo.h"

long   get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000); // секунды и микросекунды - переводим оба в миллисекунды
}

void eating(t_philo *phil)
{
    printf("Philo #%d is eating.\n", phil->number);
    usleep(phil->data->time_to_eat * 1000);
}

void sleeping(t_philo *phil)
{
    printf("Philo #%d is sleeping.\n", phil->number);
    usleep(phil->data->time_to_sleep * 1000);
}

void *action(void *structure)
{
    t_philo *phil = (t_philo*)structure;
    while(1)
    {
        eating(phil);
        sleeping(phil);
    }
    printf("SOS. I'm here!!!\n");
    //printf("%d\n", data->time_to_die);
    return (NULL);
}


int main(int argc, char**argv)
{
    t_data *data;
    pthread_t *philos;
    t_philo *phil;
    int i = -1;

    if (argc < 5 || argc > 6)
        return (1);
    data = malloc(sizeof(t_data));
    if (!data)
        return(1);
    if (check_arguments(argc, argv, data) == 1)
    {
        free(data);
        printf ("wrong arguments\n");
        return (1);
    }
    philos = malloc(sizeof(pthread_t) * data->number_of_philo);
    if(!philos)
        return (1);

    data->start_time = get_time();

    phil = malloc(sizeof(t_philo) * data->number_of_philo);
    if(!phil)
        return (1);

    while (++i < data->number_of_philo)
    {
        phil[i].number = i;
        phil[i].last_meal = data->start_time;
        phil[i].data = data;
        pthread_create(&philos[i], NULL, action, (void*)&phil[i]);
    }
    pthread_join(philos[0], NULL);
    printf("Success\n");
    return (0);
}