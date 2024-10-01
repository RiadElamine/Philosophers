/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:30:23 by relamine          #+#    #+#             */
/*   Updated: 2024/10/01 15:59:21 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_forks(t_philos	*philo)
{
	sem_wait(philo->fork);
	custom_printf(philo, "has taken a fork");
	sem_wait(philo->fork);
	custom_printf(philo, "has taken a fork");
}

void	put_forks(t_philos	*philo)
{
	custom_printf(philo, "is eating");
	sem_wait(philo->dead_lock);
	philo->last_meal = getime();
	if (philo->num_times_to_eat > 0)
		philo->num_times_to_eat--;
	sem_post(philo->dead_lock);
	ft_usleep(philo->time_to_eat);
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	ft_sleep(t_philos *philo)
{
	custom_printf(philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
	custom_printf(philo, "is thinking");
}

void	routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (create_monitor_dying(philo))
		exit(1);
	if (philo->philo_num % 2 == 0)
		ft_usleep(philo->time_to_eat);
	while (1)
	{
		take_forks(philo);
		put_forks(philo);
		sem_wait(philo->dead_lock);
		if (philo->num_times_to_eat == 0)
		{
			sem_post(philo->dead_lock);
			break ;
		}
		sem_post(philo->dead_lock);
		ft_sleep(philo);
	}
	exit(0);
}

int	main(int ac, char **av)
{
	int				*args;
	t_philos		*philos;
	pid_t			*pid;
	t_philo_args	sem_;

	philos = NULL;
	args = ft_parser(ac, av);
	if (!args)
		return (1);
	sem_unlink("/forks");
	sem_unlink("/dead_lock");
	sem_.forks = sem_open("/forks", O_CREAT, 0644, args[0]);
	if (sem_.forks == SEM_FAILED)
		return (clean(NULL, NULL, args, NULL), 1);
	sem_.dead_lock = sem_open("/dead_lock", O_CREAT, 0644, 1);
	if (sem_.dead_lock == SEM_FAILED)
		return (clean(sem_.forks, NULL, args, NULL), 1);
	if (create_philosopher_process(args, sem_, &pid, ac))
		return (clean(sem_.forks, sem_.dead_lock, args, pid), 1);
	if (join_philosophers(args[0], pid))
		return (clean(sem_.forks, sem_.dead_lock, args, pid), 1);
	return (clean(sem_.forks, sem_.dead_lock, args, pid), 0);
}
