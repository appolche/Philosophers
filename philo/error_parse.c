/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:55:47 by dleaves           #+#    #+#             */
/*   Updated: 2021/12/28 18:58:05 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_func(t_philo *phil, t_data *data)
{
	int	i;

	i = -1;
	if (data->fork)
	{
		while (++i < data->number_of_philo)
			pthread_mutex_destroy(&data->fork[i]);
		free (data->fork);
	}
	if (phil)
		free (phil);
	if (data)
		free (data);
}

int	check_arguments(int argc, char **argv, t_data *data)
{
	int	i;

	i = argc;
	while (argc > 1)
	{
		if (!positive_number(argv[argc - 1]))
			return (1);
		argc--;
	}
	data->number_of_philo = ft_atoi(argv[1]);
	if (data->number_of_philo < 1 || data->number_of_philo > 200)
		return (1);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (1);
	if (i == 6)
		data->must_eat_count = ft_atoi(argv[5]);
	else
		data->must_eat_count = -1;
	return (0);
}

int	print_message(void)
{
	printf("\n\tWrong arguments\n\n");
	printf("\nUsage: ./philo \n");
	printf("\t<number_of_philosophers>");
	printf(" - should be more than 0 and less than 200.\n");
	printf("\t<time_to_die> sould be more than 60 ms.\n");
	printf("\t<time_to_eat> sould be more than 60 ms.\n");
	printf("\t<time_to_sleep> sould be more than 60 ms.\n");
	printf("\t[number_of_times_each_philosopher_must_eat]\n\n");
	return (1);
}
