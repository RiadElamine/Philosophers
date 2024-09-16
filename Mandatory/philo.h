/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:34:37 by relamine          #+#    #+#             */
/*   Updated: 2024/09/16 19:20:04 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#define MAXINT 214748364

typedef struct s_monitor
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}					t_monitor;

typedef struct s_philos
{
	pthread_t			philo;
	int					philo_num;
	int					num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					num_times_to_eat;
	size_t				last_meal;
	size_t				start_time;
	pthread_mutex_t		fork;
	struct s_philos		*next;
	struct s_philos		*prev;
	t_monitor			*monitor;
}	t_philos;

int			*ft_parser(int ac, char **av);
int			initialize_monitor(t_monitor **monitor);
t_philos	*ft_lstnew(int *args, int i, int ac);
void		ft_lstadd_back(t_philos **lst, t_philos *new);
void		ft_lstclear(t_philos **lst);
t_philos	*ft_lstlast(t_philos *lst);
int			join_philosophers(t_philos *philos, int ac);
int			create_philosopher_threads(t_philos *philos,
				void *(*routine)(void *), int ac);
int			initialize_philosophers(t_philos **philos, t_monitor *monitor, int *args, int ac);
int			ft_usleep(size_t ms);
size_t		getime(void);
int			ft_died_or_stop(t_philos *philo);
