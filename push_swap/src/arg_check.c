/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 21:06:46 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/19 21:06:46 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	check_num(long int argc, char **argv)
{
	long int	i;
	long int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] == '-' || argv[i][j] == '+')
				j++;
			if (ft_isdigit(argv[i][j]) == 0)
			{
				write(2, "Error\n", 6);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	check_int(long int argc, char **argv)
{
	long int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi_l(argv[i]) >= 2147483648
			|| ft_atoi_l(argv[i]) <= -2147483649)
		{
			write(2, "Error\n", 6);
			exit(1);
		}
		i++;
	}
}

void	check_double(long int argc, char **argv)
{
	long int	i;
	long int	j;

	i = 1;
	while (i < argc)
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_atoi(argv[i]) == ft_atoi(argv[j]))
			{
				write(2, "Error\n", 6);
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void	check_error(long int argc, char **argv)
{
	if (argc == 1)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	check_num(argc, argv);
	check_int(argc, argv);
	check_double(argc, argv);
}
