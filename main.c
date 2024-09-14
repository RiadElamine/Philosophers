/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/09/14 22:42:29 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f(void)
{
	system("leaks philo");
}

void	take_forks(t_philos	*philo)
{
	pthread_mutex_lock(&philo->fork);
	printf("Philosopher %d takes a fork\n", philo->philo_num);
	pthread_mutex_lock(&philo->prev->fork);
	printf("Philosopher %d takes a fork\n", philo->philo_num);
	printf("Philosopher %d is Eating\n", philo->philo_num);
	philo->last_meal = getime();
	if (philo->num_times_to_eat != -1)
		philo->num_times_to_eat--;
	ft_usleep(philo->time_to_eat);
}

void	put_forks(t_philos	*philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	printf("Philosopher %d is sleeping\n", philo->philo_num);
	ft_usleep(philo->time_to_sleep);
	printf("Philosopher %d is thinking\n", philo->philo_num);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->time_to_eat);
	while (!philo->dead_flag)
	{
		if (philo->last_meal != 0)
			philo->last_meal = getime() - philo->last_meal;
		if (philo->last_meal > philo->time_to_die)
		{
			philo->dead_flag = 1;
			printf("Philosopher %d died\n", philo->philo_num);
		}
		take_forks(philo);
		put_forks(philo);
		if (philo->num_times_to_eat == 0)
			break ;
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
