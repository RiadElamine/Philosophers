/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/09/17 23:28:37 by relamine         ###   ########.fr       */
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
	if (custom_printf(philo, "takes a fork"))
		return ;
	pthread_mutex_lock(&philo->prev->fork);
	if (custom_printf(philo, "takes a fork"))
		return ;
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
	if (philo->num_times_to_eat == 0)
		return ;
	if (custom_printf(philo, "is sleeping"))
		return ;
	ft_usleep(philo->time_to_sleep);
	if (custom_printf(philo, "is thinking"))
		return ;
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	philo->start_time = getime();
	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->time_to_eat);
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
	t_monitor	*monitor;

	atexit(f);
	args = ft_parser(ac, av);
	if (!args)
		return (1);
	if (initialize_monitor(&monitor))
		return (free(args), 1);
	if (initialize_philosophers(&philos, monitor, args, ac))
		return (1);
	if (create_philosopher_threads(philos, routine, args[0]))
		return (free(args), free(monitor), 1);
	if (join_philosophers(philos, args[0]))
		return (free(args), free(monitor), 1);
	ft_lstclear(&philos);
	free(monitor);
	free(args);
	return (0);
}
