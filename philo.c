/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:45:42 by relamine          #+#    #+#             */
/*   Updated: 2024/09/15 16:02:11 by relamine         ###   ########.fr       */
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

int	initialize_philosophers(t_philos **philos, int *args, int ac)
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
			free(args);
			ft_lstclear(philos);
			return (1);
		}
		if (i == 0)
			philo_first = philo_tmp;
		ft_lstadd_back(philos, philo_tmp);
		i++;
	}
	philo_first->prev = ft_lstlast(*philos);
	philo_tmp->next = philo_first;
	return (0);
}
