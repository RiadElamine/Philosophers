/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:41:00 by relamine          #+#    #+#             */
/*   Updated: 2024/09/30 11:09:44 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (pthread_mutex_init(&philo->fork, NULL))
		return (free(philo), NULL);
	philo->next = NULL;
	philo->prev = NULL;
	return (philo);
}

t_philos	*ft_lstlast(t_philos *lst)
{
	t_philos	*ls;

	if (!lst)
		return (NULL);
	while (lst)
	{
		ls = lst;
		lst = lst->next;
	}
	return (ls);
}

void	ft_lstadd_back(t_philos **lst, t_philos *new)
{
	t_philos	*last;

	if (!lst)
		return ;
	if (!(*lst) && new)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->prev = last;
	}
}

void	ft_lstclear(t_philos **lst)
{
	t_philos	*nextnode;
	t_philos	*current;

	if (!lst)
		return ;
	current = *lst;
	pthread_mutex_destroy(&(*lst)->monitor->dead_lock);
	while (*lst)
	{
		nextnode = (*lst)->next;
		pthread_mutex_destroy(&(*lst)->fork);
		free(*lst);
		*lst = nextnode;
		if (*lst == current)
			break ;
	}
}

int	custom_printf(t_philos *philo, char *status)
{
	pthread_mutex_lock(&philo->monitor->dead_lock);
	if (philo->monitor->dead_flag == 0)
		printf("%lums Philosopher %d %s\n",
			getime() - philo->start_time, philo->philo_num, status);
	else
	{
		pthread_mutex_unlock(&philo->monitor->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->dead_lock);
	return (0);
}
