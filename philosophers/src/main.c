/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 14:16:08 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/02 14:16:08 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	milisleep(int milisec)
{
	while (milisec > 100)
	{
		usleep(100);
		milisec -= 100;
	}
	usleep(milisec);
}

void *life(void *philo)
{
	t_philo *philo_ptr;

	philo_ptr = (t_philo *)philo;

	if (philo_ptr->id % 2 == 0)
		milisleep(100);

	printf("%d is alive\n", philo_ptr->id);
	return (NULL);
}

void philo_eat(t_rules *rules)
{
	(void)(rules);
	return;
	// pthread_mutex_lock(&rules->forks[rules->philo.left_fork]);
	// pthread_mutex_lock(&rules->forks[rules->philo.right_fork]);
	// rules->philo.last_meal = timestamp();
	// printf("%d %d has taken a fork", rules->philo.last_meal, rules->philo.id);
	// milisleep(rules->time_to_eat);
	// pthread_mutex_unlock(&rules->forks[rules->philo.left_fork]);
	// pthread_mutex_unlock(&rules->forks[rules->philo.right_fork]);
}


int	lauch_philo(t_rules *rules) 
{	
	int	i;

	i = 0;
	rules->start_time = timestamp();
	while (i < rules->nb_philo)
	{
		if (pthread_create(&rules->philo[i].thread_id, NULL, life, &(rules->philo[i])))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules rules;
	
	if (argc < 5 || argc > 6)
		return (1);
	get_rules(argc, argv, &rules);
	init_philo(&rules);
	init_mutex(&rules);
	lauch_philo(&rules);
	stop_philo(&rules);
	free_mutex(&rules);
	free_philo(&rules);

	return (0);
}
