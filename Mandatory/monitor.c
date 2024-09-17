/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:54:00 by relamine          #+#    #+#             */
/*   Updated: 2024/09/17 22:36:01 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	getime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t ms)
{
	size_t	start;

	start = getime();
	while ((getime() - start) < ms)
		usleep(400);
	return (0);
}

int	ft_died_or_stop(t_philos *philo)
{
	if (philo->num_times_to_eat == 0)
		return (1);
	if (philo->last_meal != 0)
		philo->last_meal = getime() - philo->last_meal;
	pthread_mutex_lock(&philo->monitor->dead_lock);
	if (philo->monitor->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		return (1);
	}
	if (philo->last_meal > philo->time_to_die || philo->num_of_philos == 1)
	{
		pthread_mutex_lock(&philo->monitor->write_lock);
		printf("%zums Philosopher %d died\n",
			getime() - philo->start_time, philo->philo_num);
		philo->monitor->dead_flag = 1;
		pthread_mutex_unlock(&philo->monitor->write_lock);
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	return (0);
}
