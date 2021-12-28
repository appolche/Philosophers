/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 18:58:23 by dleaves           #+#    #+#             */
/*   Updated: 2021/12/28 19:00:27 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *phil)
{
	int	time_to_think;

	time_to_think = phil->data->time_to_die - phil->data->time_to_sleep
		- phil->data->time_to_eat;
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%lu ms | #%d is thinking.\n",
		(get_time() - phil->data->start_time), phil->number + 1);
	pthread_mutex_unlock(&phil->data->print_mutex);
	time_delay(time_to_think / 2);
}

void	sleeping(t_philo *phil)
{
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%lu ms | #%d is sleeping.\n",
		(get_time() - phil->data->start_time), phil->number + 1);
	pthread_mutex_unlock(&phil->data->print_mutex);
	time_delay(phil->data->time_to_sleep);
}

void	eating(t_philo *phil)
{
	pthread_mutex_lock(phil->left_fork);
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%lu ms | #%d has taken a fork.\n",
		(get_time() - phil->data->start_time), phil->number + 1);
	pthread_mutex_unlock(&phil->data->print_mutex);
	pthread_mutex_lock(phil->right_fork);
	pthread_mutex_lock(&phil->data->print_mutex);
	printf("%lu ms | #%d has taken a fork.\n",
		(get_time() - phil->data->start_time), phil->number + 1);
	printf("%lu ms | #%d is eating.\n",
		(get_time() - phil->data->start_time), phil->number + 1);
	pthread_mutex_unlock(&phil->data->print_mutex);
	phil->last_meal = get_time();
	phil->meal_counter++;
	time_delay(phil->data->time_to_eat);
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_unlock(phil->left_fork);
}

void	*action(void *structure)
{
	t_philo	*phil;

	phil = (t_philo *)structure;
	while (1)
	{
		eating(phil);
		sleeping(phil);
		thinking(phil);
	}
	return (NULL);
}
