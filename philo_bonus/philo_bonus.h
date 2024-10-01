/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:34:37 by relamine          #+#    #+#             */
/*   Updated: 2024/10/01 13:18:52 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <semaphore.h>
#include <signal.h>

#define MAXINT 214748364

typedef struct s_philos
{
	int					philo_num;
	int					num_times_to_eat;
	size_t				last_meal;
	size_t				start_time;
	sem_t				*fork;
	sem_t				*dead_lock;
	pthread_t			monitor_died;
	int					num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					dead_flag;
}	t_philos;

typedef struct s_philo_args
{
	sem_t	*forks;
	sem_t	*dead_lock;
}	t_philo_args;

int			*ft_parser(int ac, char **av);
t_philos	*ft_lstnew(int *args, int i, int ac);
void		ft_usleep(size_t ms);
size_t		getime(void);
void		custom_printf(t_philos *philo, char *status);
int			initialize_philosophers(t_philos **philos,
				int num_philo, int *args, int ac);
int			create_philosopher_process(int *args, t_philo_args sem_,
				pid_t **pid, int ac);
int			join_philosophers(int ac, pid_t *pid);
void		routine(void *arg);
void		*ft_monitor_died(void *arg);
int			ft_check_died(t_philos *philo);
int			create_monitor_dying(t_philos *philos);
void		clean(sem_t *forks, sem_t *dead_lock, int *args, int *pid);
