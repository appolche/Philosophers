/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:55:31 by dleaves           #+#    #+#             */
/*   Updated: 2021/12/28 18:55:41 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*phil_init(t_data *data)
{
	t_philo	*phil;
	int		i;

	i = -1;
	phil = malloc(sizeof(t_philo) * data->number_of_philo);
	if (!phil)
	{
		free_func(NULL, data);
		return (NULL);
	}
	while (++i < data->number_of_philo)
	{
		phil[i].number = i;
		phil[i].data = data;
		phil[i].meal_counter = 0;
		phil[i].left_fork = &data->fork[i];
		phil[i].right_fork = &data->fork[(i + 1) % phil->data->number_of_philo];
	}
	return (phil);
}

int	fork_init(t_data *data)
{
	int	i;

	i = -1;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->number_of_philo);
	if (!data->fork)
		return (0);
	while (++i < data->number_of_philo)
		pthread_mutex_init(&data->fork[i], NULL);
	return (1);
}

int	main(int argc, char**argv)
{
	t_data	*data;
	t_philo	*phil;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc < 5 || argc > 6 || (check_arguments(argc, argv, data) == 1))
	{
		free(data);
		return (print_message());
	}
	if (pthread_mutex_init(&data->print_mutex, NULL))
	{
		free(data);
		return (1);
	}
	if (!fork_init(data))
		return (1);
	phil = phil_init(data);
	if (!phil)
		return (1);
	if (!simulation(data, phil))
		return (1);
	free_func(phil, data);
	return (0);
}
