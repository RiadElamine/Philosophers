/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: relamine <relamine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 10:34:37 by relamine          #+#    #+#             */
/*   Updated: 2024/10/01 15:55:59 by relamine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define MAXINT 214748364

typedef struct s_monitor
{
	pthread_t			monitor_died;
	int					num_of_philos;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					dead_flag;
	pthread_mutex_t		dead_lock;
}					t_monitor;

typedef struct s_philos
{
	pthread_t			philo;
	int					philo_num;
	int					num_times_to_eat;
	size_t				last_meal;
	size_t				start_time;
	pthread_mutex_t		fork;
	struct s_philos		*next;
	struct s_philos		*prev;
	t_monitor			*monitor;
}	t_philos;

int			*ft_parser(int ac, char **av);
int			initialize_monitor(t_monitor **monitor, int *args);
int			create_monitor_dying(t_philos *philos);
t_philos	*ft_lstnew(int *args, int i, int ac);
void		ft_lstadd_back(t_philos **lst, t_philos *new);
void		ft_lstclear(t_philos **lst);
t_philos	*ft_lstlast(t_philos *lst);
int			join_philosophers(t_philos *philos, int ac);
int			create_philosopher_threads(t_philos *philos,
				void *(*routine)(void *), int ac);
int			initialize_philosophers(t_philos **philos,
				t_monitor *monitor, int *args, int ac);
int			ft_usleep(size_t ms, t_philos *philo);
size_t		getime(void);
void		*ft_monitor_died(void *arg);
int			custom_printf(t_philos *philo, char *status);

#endif