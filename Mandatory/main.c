/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/09/24 00:51:59 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	f(void)
{
	system("leaks philo");
}

int	take_forks(t_philos	*philo)
{
	pthread_mutex_lock(&philo->fork);
	custom_printf(philo, "takes a fork");
	if (philo->monitor->num_of_philos == 1)
	{
		ft_usleep(philo->monitor->time_to_die);
		return (pthread_mutex_unlock(&philo->fork), 0);
	}
	pthread_mutex_lock(&philo->prev->fork);
	custom_printf(philo, "takes a fork");
	return (1);
}

void	put_forks(t_philos	*philo)
{
	if (custom_printf(philo, "is Eating"))
		return (pthread_mutex_unlock(&philo->fork), pthread_mutex_unlock(&philo->prev->fork), (void)0);
	pthread_mutex_lock(&philo->monitor->dead_lock);
	philo->last_meal = getime();
	if (philo->num_times_to_eat != -1)
		philo->num_times_to_eat--;
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	ft_usleep(philo->monitor->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
}

int	ft_sleep(t_philos *philo)
{
	if (custom_printf(philo, "is sleeping"))
		return (1);
	ft_usleep(philo->monitor->time_to_sleep);
	if (custom_printf(philo, "is thinking"))
		return (1);
	return (0);
}

int	ft_died_or_stop(t_philos *philo)
{
	if (philo->monitor->num_of_philos== 1)
		return (1);
	pthread_mutex_lock(&philo->monitor->dead_lock);
	if (philo->num_times_to_eat == 0 || philo->monitor->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	return (0);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->monitor->time_to_eat);
	while (1)
	{
		if (take_forks(philo))
			put_forks(philo);
		if (ft_died_or_stop(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			*args;
	t_philos	*philos;
	t_monitor	*monitor;

	// atexit(f);
	philos = NULL;
	args = ft_parser(ac, av);
	if (!args)
		return (1);
	if (initialize_monitor(&monitor, args))
		return (free(args), 1);
	if (initialize_philosophers(&philos, monitor, args, ac))
		return (1);
	if (initialize_monitor_died(philos))
		return (1);
	usleep(1000);
	if (create_philosopher_threads(philos, routine, args[0]))
		return (free(args), free(monitor), 1);
	if (join_philosophers(philos, args[0]))
		return (free(args), free(monitor), 1);
	ft_lstclear(&philos);
	free(monitor);
	free(args);
	return (0);
}
