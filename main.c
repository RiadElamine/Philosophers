/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/09/13 07:01:53 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f(void)
{
	system("leaks philo");
}
t_monitor	monitor;
monitor.dead_flag = 0;
pthread_mutex_init(&monitor.mutex, NULL);


void	take_forks(t_philos	*philo)
{
	pthread_mutex_lock(&philo->fork);
	printf("Philosopher %d takes a fork\n", philo->philo_num);
	pthread_mutex_lock(&philo->prev->fork);
	printf("Philosopher %d takes a fork\n", philo->philo_num);
	printf("Philosopher %d is Eating\n", philo->philo_num);
	usleep(philo->time_to_eat);
}

void	put_forks(t_philos	*philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	printf("Philosopher %d is sleeping\n", philo->philo_num);
	usleep(philo->time_to_sleep);
	printf("Philosopher %d is thinking\n", philo->philo_num);
}

void	*routine(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	if (philo->philo_num % 2 == 0)
		usleep(philo->time_to_eat);
	i = 0;
	philo->start_time = getime();
	while (1)
	{
		// exit(0);
		take_forks(philo);
		put_forks(philo);

		if (getime() - philo->start_time > philo->time_to_die)
		{
			printf("Philosopher %d died\n", philo->philo_num);
			break;
		}
		printf("---- %ld %ld\n", getime() - philo->start_time, philo->time_to_die);
		// if (i == 10)
		// 	exit(0); 
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			*args;
	t_philos	*philos;

	args = ft_parser(ac, av);
	if (!args)
		return (1);
	if (initialize_philosophers(&philos, args, ac))
		return (1);
	ac = args[0];
	free(args);
	if (create_philosopher_threads(philos, routine, ac))
		return (1);
	if (join_philosophers(philos, ac))
		return (1);
	destroying_mutexes(philos);
	printf("All threads finished\n");
	return (0);
}
