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

void	*ft_killer(void *structure)
{
	t_philo	*phil;

	phil = (t_philo *)structure;
	while (1)
	{
		if ((get_time() - phil->last_meal) > phil->data->time_to_die)
		{
			print_death_notice(phil);
			exit(1);
		}		
		usleep(100);
	}
}

void	thinking(t_philo *phil)
{
	int	time_to_think;

	time_to_think = phil->data->time_to_die - phil->data->time_to_sleep
		- phil->data->time_to_eat;
	sem_wait(phil->data->print_access);
	printf("%lu ms | #%d is thinking.\n",
		(get_time() - phil->data->start_time), phil->number);
	sem_post(phil->data->print_access);
	time_delay(time_to_think / 2);
}

void	sleeping(t_philo *phil)
{
	sem_wait(phil->data->print_access);
	printf("%lu ms | #%d is sleeping.\n",
		(get_time() - phil->data->start_time), phil->number);
	sem_post(phil->data->print_access);
	time_delay(phil->data->time_to_sleep);
}

void	eating(t_philo *phil)
{
	sem_wait(phil->data->print_access);
	printf("%lu ms | #%d is eating.\n",
		(get_time() - phil->data->start_time), phil->number);
	sem_post(phil->data->print_access);
	time_delay(phil->data->time_to_eat);
	sem_post(phil->forks);
	sem_post(phil->forks);
	phil->meal_counter++;
	if (phil->data->must_eat_count >= 0
			&& phil->meal_counter >= phil->data->must_eat_count)
		exit(2);
}

void grab_forks(t_philo *phil)
{
	sem_wait(phil->forks);
	sem_wait(phil->data->print_access);
	printf("%lu ms | #%d has taken a fork.\n",
		(get_time() - phil->data->start_time), phil->number);
	sem_post(phil->data->print_access);
	sem_wait(phil->forks);
	phil->last_meal = get_time();
	sem_wait(phil->data->print_access);
	printf("%lu ms | #%d has taken a fork.\n",
		(get_time() - phil->data->start_time), phil->number);
	sem_post(phil->data->print_access);
}

int	action(t_philo	*phil, t_data *data)
{
	pthread_create(&data->thread, NULL, ft_killer, (void *)phil);
	pthread_detach(data->thread);
	while (1)
	{
		grab_forks(phil);
		eating(phil);
		sleeping(phil);
		thinking(phil);
	}
	return (0);
}
