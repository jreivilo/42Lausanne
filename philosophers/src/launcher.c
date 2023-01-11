/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:38:03 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/11 14:07:11 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_eat(t_philo *philo, t_rules *rules)
{
	pthread_mutex_lock(&rules->forks[philo->id - 1]);
	if (rules->stop == 0)
		printf("%lld %d has taken a fork\n",
			time_diff(rules->start_time, timestamp()), philo->id);
	pthread_mutex_lock(&rules->forks[philo->id % rules->nb_philo]);
	if (rules->stop == 0)
		printf("%lld %d has taken a fork\n",
			time_diff(rules->start_time, timestamp()), philo->id);
	if (rules->stop == 0)
		printf("%lld %d is eating\n",
			time_diff(rules->start_time, timestamp()), philo->id);
	philo->last_meal = time_diff(rules->start_time, timestamp());
	if (rules->nb_meal != -1)
		philo->nb_meal++;
	milisleep(rules->time_to_eat);
	pthread_mutex_unlock(&rules->forks[philo->id - 1]);
	pthread_mutex_unlock(&rules->forks[philo->id % rules->nb_philo]);
}

void	philo_sleep(t_philo *philo, t_rules *rules)
{
	if (rules->stop == 0)
		printf("%lld %d is sleeping\n",
			time_diff(rules->start_time, timestamp()), philo->id);
	milisleep(rules->time_to_sleep);
}

void	philo_think(t_philo *philo, t_rules *rules)
{
	if (rules->stop == 0)
		printf("%lld %d is thinking\n",
			time_diff(rules->start_time, timestamp()), philo->id);
}

void	*life(void *philo)
{
	t_philo	*philo_ptr;

	philo_ptr = (t_philo *)philo;
	if (philo_ptr->id % 2 == 0)
		usleep(1000);
	while (philo_ptr->rules->stop == 0)
	{
		if (philo_ptr->rules->stop == 0)
			philo_eat(philo_ptr, philo_ptr->rules);
		if (philo_ptr->rules->stop == 0)
			philo_sleep(philo_ptr, philo_ptr->rules);
		if (philo_ptr->rules->stop == 0)
			philo_think(philo_ptr, philo_ptr->rules);
	}
	return (NULL);
}

int	lauch_philo(t_rules *rules)
{	
	int	i;

	i = 0;
	rules->start_time = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread_id, NULL,
				life, &rules->philo[i]))
			return (1);
		i++;
	}
	monitor(rules);
	if (rules->nb_philo > 1)
		stop_philo(rules);
	return (0);
}
