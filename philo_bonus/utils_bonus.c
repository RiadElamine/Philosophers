/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:41:00 by relamine          #+#    #+#             */
/*   Updated: 2024/10/01 13:01:41 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philos	*ft_lstnew(int *args, int i, int ac)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->philo_num = i;
	philo->start_time = getime();
	if (ac == 6)
		philo->num_times_to_eat = args[4];
	else
		philo->num_times_to_eat = -1;
	philo->last_meal = getime();
	philo->dead_flag = 0;
	philo->num_of_philos = args[0];
	philo->time_to_die = args[1];
	philo->time_to_eat = args[2];
	philo->time_to_sleep = args[3];
	return (philo);
}

void	custom_printf(t_philos *philo, char *status)
{
	sem_wait(philo->dead_lock);
	if (philo->dead_flag == 0)
		printf("%lums Philosopher %d %s\n",
			getime() - philo->start_time, philo->philo_num, status);
	sem_post(philo->dead_lock);
	return ;
}

int	create_monitor_dying(t_philos *philos)
{
	if (pthread_create(&philos->monitor_died, NULL,
			ft_monitor_died, philos) != 0)
	{
		printf("Error: Thread creation failed\n");
		return (1);
	}
	pthread_detach(philos->monitor_died);
	return (0);
}

void	clean(sem_t *forks, sem_t *dead_lock, int *args, int *pid)
{
	if (pid)
		free(pid);
	if (forks)
	{
		sem_close(forks);
		sem_unlink("/forks");
	}
	if (dead_lock)
	{
		sem_close(dead_lock);
		sem_unlink("/dead_lock");
	}
	if (args)
		free(args);
}
