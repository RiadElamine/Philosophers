/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:41:00 by relamine          #+#    #+#             */
/*   Updated: 2024/09/16 18:57:15 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philos	*ft_lstnew(int *args, int i, int ac)
{
	t_philos	*philo;

	philo = malloc(sizeof(t_philos));
	if (!philo)
		return (NULL);
	philo->philo_num = i + 1;
	philo->num_of_philos = args[0];
	philo->time_to_die = args[1];
	philo->time_to_eat = args[2];
	philo->time_to_sleep = args[3];
	if (ac == 6)
		philo->num_times_to_eat = args[4];
	else
		philo->num_times_to_eat = -1;
	philo->last_meal = 0;
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
