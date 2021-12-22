#include "philo.h"

long   get_time(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000); // секунды и микросекунды - переводим оба в миллисекунды
}

void * ft_killer(void *structure)
{
    t_philo *phil = (t_philo*) structure;
    int i;

    i = -1;

    while (1)
    {
        i = -1;
        while (++i < phil->data->number_of_philo)
        {
            if ((get_time() - phil[i].last_meal) >= phil->data->time_to_die)
            {
                printf("%lu ms | Phil #%d died. \n", (get_time() - phil->data->start_time), phil[i].number);
                return (NULL);
            }
            else if (phil->data->must_eat_count >= 0 && phil[i].meal_counter >= phil->data->must_eat_count)
            {
                printf("%lu ms | simulation stopped\n", (get_time() - phil->data->start_time));
                return (NULL);
            }
        }
    }
}

pthread_mutex_t *fork_parsing(t_data *data, pthread_mutex_t *fork)
{
    int         j;

    j = -1;
    fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
    if (!fork)
         return (NULL);
    while (++j < data->number_of_philo)
    {
        pthread_mutex_init(&fork[j], NULL);
    }
    return (fork);
}

int simulation (t_data *data)
{
    pthread_t   *thread; 
    t_philo     *phil;
    pthread_mutex_t *fork;
    int         i;

    i = -1;
    fork = NULL;
    thread = malloc(sizeof(pthread_t) * data->number_of_philo + 1);
    if (!thread)
        return (0);
    phil = malloc(sizeof(t_philo) * data->number_of_philo);
    if (!phil)
        return (0);
    fork = fork_parsing(data, fork);
    if (!fork)
        return(0);
    data->start_time = get_time();
    printf("start_time: %lu\n", data->start_time);
    while (++i < data->number_of_philo)
    {
        phil[i].number = i;
        phil[i].last_meal = data->start_time;
        phil[i].data = data;
        phil[i].meal_counter = 0;
        phil[i].left_fork = &fork[i];
        phil[i].right_fork = &fork[(i + 1) % phil->data->number_of_philo];
        pthread_create(&thread[i], NULL, action, (void*)&phil[i]);
        usleep(100);
    }
    pthread_create(&thread[i], NULL, ft_killer, (void*)phil);
    pthread_join(thread[i], NULL);
    return (0);
}

int main(int argc, char**argv)
{
    t_data *data;

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
    if (!simulation(data))
        return (1);
    printf("Success\n");
    return (0);
}