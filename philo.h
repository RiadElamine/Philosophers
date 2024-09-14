/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:34:37 by relamine          #+#    #+#             */
/*   Updated: 2024/09/14 22:30:49 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAXINT 214748364

typedef struct s_philos
{
	pthread_t			philo;
	int					philo_num;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					num_times_to_eat;
	size_t				last_meal;
	pthread_mutex_t		fork;
	int					dead_flag;
	struct s_philos		*next;
	struct s_philos		*prev;
}	t_philos;

int			*ft_parser(int ac, char **av);
t_philos	*ft_lstnew(int *args, int i, int ac);
void		ft_lstadd_back(t_philos **lst, t_philos *new);
void		ft_lstclear(t_philos **lst);
t_philos	*ft_lstlast(t_philos *lst);
int			join_philosophers(t_philos *philos, int ac);
int			create_philosopher_threads(t_philos *philos,
				void *(*routine)(void *), int ac);
int			initialize_philosophers(t_philos **philos, int *args, int ac);
void		destroying_mutexes(t_philos	*philos);
int			ft_usleep(size_t ms);
size_t		getime(void);
