/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:54:00 by relamine          #+#    #+#             */
/*   Updated: 2024/09/29 04:37:00 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	getime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t ms, t_philos *philo)
{
	size_t	start;

	start = getime();
	while ((getime() - start) < ms)
	{
		pthread_mutex_lock(&philo->monitor->dead_lock);
		if (philo->monitor->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->monitor->dead_lock);
			return (1);
		}
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		usleep(400);
	}
	return (0);
}

int	ft_check_died(t_philos *philo)
{
	pthread_mutex_lock(&philo->monitor->dead_lock);
	if (philo->monitor->dead_flag == 1)
	{
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		return (1);
	}
	if ((getime() - philo->last_meal) > philo->monitor->time_to_die)
	{
		printf("%zums Philosopher %d died\n",
			(getime() - philo->start_time), philo->philo_num);
		philo->monitor->dead_flag = 1;
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	return (0);
}

int	ft_check_stpeating(t_philos *philo, int *i)
{
	pthread_mutex_lock(&philo->monitor->dead_lock);
	if (philo->num_times_to_eat == 0)
	{
		philo->num_times_to_eat--;
		(*i)--;
		if ((*i) == 0)
		{
			philo->monitor->dead_flag = 1;
			pthread_mutex_unlock(&philo->monitor->dead_lock);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	return (0);
}

void	*ft_monitor_died(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	i = philo->monitor->num_of_philos;
	while (1)
	{
		if (ft_check_died(philo) || ft_check_stpeating(philo, &i))
			break ;
		philo = philo->next;
	}
	return (NULL);
}
