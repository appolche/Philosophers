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

void	print_death_notice(t_philo	*phil)
{
	sem_wait(phil->data->print_access);
	printf("%lu ms | #%d died. \n",
		(get_time() - phil->data->start_time), phil->number);
}

int	simulation(t_data *data, t_philo *phil)
{
	int	i;
	int status;
	pid_t pid;

	i = -1;
	data->start_time = get_time();
	while (++i < data->number_of_philo)
	{
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
		{
			phil[i].last_meal = data->start_time;
			action(&phil[i], data);
		}
		else
		{
			phil[i].pid = pid;
		}
	}
	wait(&status);
	if (WEXITSTATUS(status) == 1)
		kill(0, SIGTERM);
	else 
	{
		while (++i < data->number_of_philo)
			printf("%d - ", phil[i].pid);
		i = -1;
		while (++i < data->number_of_philo)
			waitpid(phil[i].pid, NULL, 0);
	}
	return (0);
}
