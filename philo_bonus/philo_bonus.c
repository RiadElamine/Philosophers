/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:45:42 by relamine          #+#    #+#             */
/*   Updated: 2024/10/01 13:18:37 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	join_philosophers(int ac, pid_t *pid)
{
	int			i;
	int			status;
	int			j;

	i = 0;
	while (i < ac)
	{
		if (waitpid(-1, &status, 0) == -1)
		{
			printf("Error: Waitpid failed\n");
			return (1);
		}
		if (WIFEXITED(status) && WEXITSTATUS(status))
		{
			j = 0;
			while (j < ac)
			{
				kill(pid[j], SIGKILL);
				j++;
			}
			break ;
		}
		i++;
	}
	return (0);
}

int	create_philosopher_process(int *args, t_philo_args sem_,
		pid_t **pid, int ac)
{
	int			i;
	t_philos	*philos;

	i = 0;
	philos = NULL;
	*pid = malloc(sizeof(pid_t) * args[0]);
	if (!*pid)
		return (printf("Error: Malloc failed\n"), 1);
	while (i < args[0])
	{
		(*pid)[i] = fork();
		if ((*pid)[i] == -1)
			return (printf("Error: Fork failed\n"), 1);
		if ((*pid)[i] == 0)
		{
			if (initialize_philosophers(&philos, i + 1, args, ac))
				exit(1);
			philos->fork = sem_.forks;
			philos->dead_lock = sem_.dead_lock;
			routine(philos);
		}
		i++;
	}
	return (0);
}

int	initialize_philosophers(t_philos **philos, int num_philo,
	int *args, int ac)
{
	*philos = ft_lstnew(args, num_philo, ac);
	if (!*philos)
	{
		free(args);
		return (1);
	}
	return (0);
}
