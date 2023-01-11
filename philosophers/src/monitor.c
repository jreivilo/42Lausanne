/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:15:29 by jolivier          #+#    #+#             */
/*   Updated: 2023/01/11 12:38:21 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_dead(t_philo *philo, t_rules *rules)
{
	if (time_diff(philo->last_meal, time_diff(rules->start_time, timestamp()))
		>= rules->time_to_die)
	{
		rules->stop = 1;
		printf("%lld %d died\n",
			time_diff(rules->start_time, timestamp()), philo->id);
	}
}

void	philo_meal(t_philo *philo, t_rules *rules)
{
	if (philo->nb_meal >= rules->nb_meal && rules->nb_meal != -1)
	{
		rules->nb_philo_eat++;
	}
}

void	monitor(t_rules *rules)
{
	int	i;

	while (rules->stop == 0)
	{
		i = 0;
		rules->nb_philo_eat = 0;
		while (i < rules->nb_philo && rules->stop == 0)
		{
			philo_dead(&rules->philo[i], rules);
			philo_meal(&rules->philo[i], rules);
			if (rules->nb_philo_eat == rules->nb_philo)
			{
				rules->stop = 1;
				return ;
			}
			i++;
		}
	}
	return ;
}
