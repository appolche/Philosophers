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
		phil[i].number = i + 1;
		phil[i].data = data;
		phil[i].meal_counter = 0;
		phil[i].forks = data->forks;
	}
	return (phil);
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
	sem_unlink("/forks");
	sem_unlink("/print");
	data->forks = sem_open("/forks", O_CREAT | O_EXCL, S_IRWXU, data->number_of_philo);
	data->print_access = sem_open("/print", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (data->forks == SEM_FAILED || data->print_access == SEM_FAILED)
		return (1);
	phil = phil_init(data);
	if (!phil)
		return (1);
	simulation(data, phil);
	free_func(phil, data);
	return (0);
}
