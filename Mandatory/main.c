/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/09/29 03:56:24 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philos	*philo)
{
	pthread_mutex_lock(&philo->fork);
	if (custom_printf(philo, "takes a fork")
		|| philo->monitor->num_of_philos == 1)
		return (pthread_mutex_unlock(&philo->fork), 0);
	pthread_mutex_lock(&philo->prev->fork);
	if (custom_printf(philo, "takes a fork"))
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->prev->fork), 0);
	return (1);
}

int	put_forks(t_philos	*philo)
{
	if (custom_printf(philo, "is Eating"))
		return (pthread_mutex_unlock(&philo->fork),
			pthread_mutex_unlock(&philo->prev->fork), 0);
	pthread_mutex_lock(&philo->monitor->dead_lock);
	philo->last_meal = getime();
	if (philo->num_times_to_eat != -1)
		philo->num_times_to_eat--;
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	ft_usleep(philo->monitor->time_to_eat, philo);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->prev->fork);
	return (1);
}

int	ft_sleep(t_philos *philo)
{
	pthread_mutex_lock(&philo->monitor->dead_lock);
	if (philo->num_times_to_eat == 0 || philo->monitor->dead_flag == 1)
		return (pthread_mutex_unlock(&philo->monitor->dead_lock), 0);
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	if (custom_printf(philo, "is sleeping"))
		return (0);
	ft_usleep(philo->monitor->time_to_sleep, philo);
	if (custom_printf(philo, "is thinking"))
		return (0);
	return (1);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->monitor->time_to_eat, philo);
	while (1)
	{
		if (!take_forks(philo))
			break ;
		if (!put_forks(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	int			*args;
	t_philos	*philos;
	t_monitor	*monitor;

	philos = NULL;
	args = ft_parser(ac, av);
	if (!args)
		return (1);
	if (initialize_monitor(&monitor, args))
		return (free(args), 1);
	if (initialize_philosophers(&philos, monitor, args, ac))
		return (1);
	if (create_monitor_dying(philos))
		return (free(args), free(monitor), 1);
	if (create_philosopher_threads(philos, routine, args[0]))
		return (free(args), free(monitor), 1);
	if (join_philosophers(philos, args[0]))
		return (free(args), free(monitor), 1);
	ft_lstclear(&philos);
	free(monitor);
	free(args);
	return (0);
}
