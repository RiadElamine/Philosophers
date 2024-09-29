/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:45:42 by relamine          #+#    #+#             */
/*   Updated: 2024/09/29 04:36:49 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_philosophers(t_philos *philos, int ac)
{
	t_philos	*philo_tmp;
	int			i;

	philo_tmp = philos;
	i = 0;
	while (i < ac)
	{
		if (pthread_join(philo_tmp->philo, NULL) != 0)
		{
			printf("Error: Thread join failed\n");
			ft_lstclear(&philos);
			return (1);
		}
		i++;
		philo_tmp = philo_tmp->next;
	}
	if (pthread_join(philos->monitor->monitor_died, NULL) != 0)
	{
		printf("Error: Thread join failed\n");
		ft_lstclear(&philos);
		return (1);
	}
	return (0);
}

int	create_philosopher_threads(t_philos *philos,
									void *(*routine)(void *), int ac)
{
	t_philos	*philo_tmp;
	int			i;

	philo_tmp = philos;
	i = 0;
	while (i < ac)
	{
		if (pthread_create(&philo_tmp->philo, NULL, routine, philo_tmp) != 0)
		{
			printf("Error: Thread creation failed\n");
			ft_lstclear(&philos);
			return (1);
		}
		i++;
		philo_tmp = philo_tmp->next;
	}
	return (0);
}

int	initialize_monitor(t_monitor **monitor, int *args)
{
	(*monitor) = malloc(sizeof(t_monitor));
	if (!(*monitor))
		return (1);
	if (pthread_mutex_init(&(*monitor)->dead_lock, NULL))
		return (free((*monitor)), 1);
	(*monitor)->dead_flag = 0;
	(*monitor)->num_of_philos = args[0];
	(*monitor)->time_to_die = args[1];
	(*monitor)->time_to_eat = args[2];
	(*monitor)->time_to_sleep = args[3];
	return (0);
}

int	initialize_philosophers(t_philos **philos,
	t_monitor *monitor, int *args, int ac)
{
	t_philos	*philo_tmp;
	t_philos	*philo_first;
	int			i;

	i = 0;
	*philos = NULL;
	while (i < args[0])
	{
		philo_tmp = ft_lstnew(args, i + 1, ac);
		if (!philo_tmp)
		{
			ft_lstclear(philos);
			free(monitor);
			free(args);
			return (1);
		}
		if (i == 0)
			philo_first = philo_tmp;
		philo_tmp->monitor = monitor;
		ft_lstadd_back(philos, philo_tmp);
		i++;
	}
	philo_first->prev = ft_lstlast(*philos);
	philo_tmp->next = philo_first;
	return (0);
}

int	create_monitor_dying(t_philos *philos)
{
	if (pthread_create(&philos->monitor->monitor_died, NULL,
			ft_monitor_died, philos) != 0)
	{
		printf("Error: Thread creation failed\n");
		ft_lstclear(&philos);
		return (1);
	}
	return (0);
}
