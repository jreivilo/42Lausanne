/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:09:35 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/28 16:09:35 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <pthread.h>

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				nb_meal;
	long long		last_meal;
	int				is_dead;
	struct s_rules	*rules;
	pthread_t		thread_id;
}	t_philo;

typedef struct s_rules
{
	int				nb_philo;
	long long		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meal;
	int				nb_philo_eat;
	int				stop;
	long long		start_time;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_t		monitor;
}	t_rules;

int			ft_atoi(const char *str);

long long	timestamp(void);
long long	time_diff(long long start, long long end);
void		milisleep(long long milisec);

int			get_rules(int argc, char **argv, t_rules *rules);
void		init_philo(t_rules *rules);
void		init_mutex(t_rules *rules);
int			lauch_philo(t_rules *rules);
void		monitor(t_rules *rules);

void		stop_philo(t_rules *rules);
void		free_mutex(t_rules *rules);
void		free_philo(t_rules *rules);

#endif