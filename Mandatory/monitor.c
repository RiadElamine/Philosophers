/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:54:00 by relamine          #+#    #+#             */
/*   Updated: 2024/09/24 00:51:49 by relamine         ###   ########.fr       */
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

void	*ft_monitor_died(void *arg)
{
	t_philos	*philo;
	int			i;

	philo = (t_philos *)arg;
	i = philo->monitor->num_of_philos;
	while (i)
	{
		pthread_mutex_lock(&philo->monitor->dead_lock);
		if (philo->num_times_to_eat == 0)
		{
			philo = philo->next;
			i--;
			pthread_mutex_unlock(&philo->monitor->dead_lock);
			continue ;
		}
		if (philo->monitor->dead_flag == 1)
		{
			pthread_mutex_unlock(&philo->monitor->dead_lock);
			return (NULL);
		}
		if ((getime() - philo->last_meal) > philo->monitor->time_to_die)
		{
			printf("%zums Philosopher %d died\n",
				(getime() - philo->start_time), philo->philo_num);
			philo->monitor->dead_flag = 1;
			pthread_mutex_unlock(&philo->monitor->dead_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		philo = philo->next;
	}
	return (NULL);
}

int	initialize_monitor_died(t_philos *philos)
{
	pthread_t	monitor_died;

	if (pthread_create(&monitor_died, NULL,
			ft_monitor_died, philos) != 0)
	{
		printf("Error: Thread creation failed\n");
		return (1);
	}
	pthread_detach(monitor_died);
	return (0);
}
