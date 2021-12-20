#include "philo.h"

int check_arguments(int argc, char **argv, t_data *data)
{
    int  i;

    i = argc;
    while (argc > 1)
    {
        if (!pos_number(argv[argc - 1]))
            return (1);
        argc--;
    }
    data->number_of_philo = ft_atoi(argv[1]);
    if (data->number_of_philo < 2)
    {
        printf ("Number of philo should be more than 1\n");
        return (1);
    }
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep= ft_atoi(argv[4]);
    if (i == 6)
        data->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
    else 
        data->number_of_times_each_philosopher_must_eat = -1;
    return (0);
}