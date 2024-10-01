/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 05:54:00 by relamine          #+#    #+#             */
/*   Updated: 2024/10/01 15:59:29 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	getime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t ms)
{
	size_t	start;

	start = getime();
	while ((getime() - start) < ms)
		usleep(400);
}

int	ft_check_died(t_philos *philo)
{
	sem_wait(philo->dead_lock);
	if ((getime() - philo->last_meal) > philo->time_to_die)
	{
		printf("%zu %d died\n",
			(getime() - philo->start_time), philo->philo_num);
		philo->dead_flag = 1;
		exit(1);
	}
	if (philo->num_times_to_eat == 0)
	{
		sem_post(philo->dead_lock);
		return (1);
	}
	sem_post(philo->dead_lock);
	return (0);
}

void	*ft_monitor_died(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		if (ft_check_died(philo))
			break ;
	}
	return (NULL);
}
