/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:45:42 by relamine          #+#    #+#             */
/*   Updated: 2024/09/17 23:28:58 by relamine         ###   ########.fr       */
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

int	initialize_monitor(t_monitor **monitor)
{
	(*monitor) = malloc(sizeof(t_monitor));
	if (!(*monitor))
		return (1);
	if (pthread_mutex_init(&(*monitor)->dead_lock, NULL))
		return (free((*monitor)), 1);
	if (pthread_mutex_init(&(*monitor)->write_lock, NULL))
		return (pthread_mutex_destroy(&(*monitor)->dead_lock),
			free((*monitor)), 1);
	(*monitor)->dead_flag = 0;
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
		philo_tmp = ft_lstnew(args, i, ac);
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
