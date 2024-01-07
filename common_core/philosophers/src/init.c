/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 17:56:36 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/30 17:56:36 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				printf("Error: invalid arguments\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	get_rules(int argc, char **argv, t_rules *rules)
{
	if (check_args(argc, argv) == 1)
		return (1);
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->stop = 0;
	if (argc == 6)
		rules->nb_meal = ft_atoi(argv[5]);
	else
		rules->nb_meal = -1;
	if (rules->nb_philo < 1 || rules->time_to_die <= 0
		|| rules->time_to_eat < 0 || rules->time_to_sleep < 0
		|| (argc == 6 && rules->nb_meal < 1))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	return (0);
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	rules->philo = malloc(sizeof(t_philo) * rules->nb_philo);
	while (i < rules->nb_philo)
	{
		rules->philo[i].id = i + 1;
		rules->philo[i].left_fork = i;
		rules->philo[i].right_fork = (i + 1) % rules->nb_philo;
		rules->philo[i].nb_meal = 0;
		rules->philo[i].last_meal = 0;
		rules->philo[i].is_dead = 0;
		rules->philo[i].rules = rules;
		i++;
	}
}

void	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	rules->forks = malloc(sizeof(pthread_mutex_t) * (rules->nb_philo * 2 - 1));
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
}
