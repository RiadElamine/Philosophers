/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/09/15 16:04:26 by relamine         ###   ########.fr       */
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
	printf("%zums Philosopher %d takes a fork\n",
		getime() - philo->start_time, philo->philo_num);
	pthread_mutex_lock(&philo->prev->fork);
	printf("%zums Philosopher %d takes a fork\n",
		getime() - philo->start_time, philo->philo_num);
	printf("%zums Philosopher %d is Eating\n",
		getime() - philo->start_time, philo->philo_num);
	philo->last_meal = getime();
	if (philo->num_times_to_eat != -1)
		philo->num_times_to_eat--;
	ft_usleep(philo->time_to_eat);
}

void	put_forks(t_philos	*philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	printf("%zums Philosopher %d is sleeping\n",
		getime() - philo->start_time, philo->philo_num);
	ft_usleep(philo->time_to_sleep);
	printf("%zums Philosopher %d is thinking\n",
		getime() - philo->start_time, philo->philo_num);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->time_to_eat);
	philo->start_time = getime();
	while (!ft_died_or_stop(philo))
	{
		take_forks(philo);
		put_forks(philo);
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
	ft_lstclear(&philos);
	printf("All threads finished\n");
	return (0);
}
