/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_start.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 19:00:59 by dleaves           #+#    #+#             */
/*   Updated: 2021/12/28 19:09:44 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death_notice(t_philo	*phil, int i)
{
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%lu ms | #%d died. \n",
		(get_time() - phil->data->start_time), phil[i].number + 1);
}

void	*ft_killer(void *structure)
{
	t_philo	*phil;
	int		i;

	i = -1;
	phil = (t_philo *)structure;
	while (1)
	{
		i = -1;
		while (++i < phil->data->number_of_philo)
		{
			if ((get_time() - phil[i].last_meal) > phil->data->time_to_die)
			{
				print_death_notice(phil, i);
				return (NULL);
			}
			else if (phil->data->must_eat_count >= 0
				&& phil[i].meal_counter > phil->data->must_eat_count)
			{
				pthread_mutex_lock(&phil->data->print_mutex);
				return (NULL);
			}
		}
		usleep(100);
	}
}

int	simulation(t_data *data, t_philo *phil)
{
	int	i;

	i = -1;
	data->thread = malloc(sizeof(pthread_t) * data->number_of_philo + 1);
	if (!data->thread)
		return (1);
	data->start_time = get_time();
	while (++i < data->number_of_philo)
	{
		phil[i].last_meal = data->start_time;
		pthread_create(&data->thread[i], NULL, action, (void *)&phil[i]);
		pthread_detach(data->thread[i]);
		usleep(100);
	}
	pthread_create(&data->thread[i], NULL, ft_killer, (void *)phil);
	pthread_join(data->thread[i], NULL);
	usleep(500000);
	return (0);
}
