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

int	main(int argc, char **argv)
{
	t_rules	rules;

	if (argc < 5 || argc > 6)
	{
		printf("Error: invalid number of arguments\n");
		return (1);
	}
	if (get_rules(argc, argv, &rules) == 1)
		return (1);
	init_philo(&rules);
	init_mutex(&rules);
	lauch_philo(&rules);
	free_philo(&rules);
	free_mutex(&rules);
	return (0);
}
