/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 19:00:47 by dleaves           #+#    #+#             */
/*   Updated: 2021/12/28 19:10:06 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h> 
# include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
# include <sys/time.h>
# include <semaphore.h>
# include <pthread.h>

typedef struct s_data
{
	int				number_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	pthread_t		thread;
	sem_t			*forks;
	sem_t			*print_access;
}	t_data;

typedef struct s_philo
{
	int				number;
	pid_t			pid;
	int				meal_counter;
	long			last_meal;
	sem_t			*forks;
	t_data			*data;
}	t_philo;

int		check_arguments(int argc, char **argv, t_data *data);
int		print_message(void);
int		ft_atoi(const char *str);
int		positive_number(char *str);
long	get_time(void);
int		simulation(t_data *data, t_philo *phil);
t_philo	*phil_init(t_data *data);
void	*ft_killer(void *structure);
int		action(t_philo	*phil, t_data *data);
void	eating(t_philo *phil);
void	sleeping(t_philo *phil);
void	thinking(t_philo *phil);
void	time_delay(int time_to_waste);
void	free_func(t_philo *phil, t_data *data);
void	print_death_notice(t_philo	*phil);

#endif
