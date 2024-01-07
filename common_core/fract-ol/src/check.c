/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:28:15 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/01 18:13:30 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	check_julia_args(char **argv)
{
	check_number(argv[2]);
	check_number(argv[3]);
}

void	check_number(char *str)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	p = norminette(str + i);
	if (p == 0)
	{
		ft_putstr("Error: Wrong argument\n");
		ft_putstr("Correct number : 2.0 or -0.09\n");
		exit(0);
	}
}

int	norminette(char *str)
{
	int	i;
	int	p;

	i = 0;
	p = 0;
	while (str[i])
	{
		if (str[i] == '.')
		{
			i++;
			p++;
		}
		if (str[i] < '0' || str[i] > '9' || p > 1)
		{
			ft_putstr("Error: Wrong argument\n");
			ft_putstr("corect number example : 1.0 0.0 -0.366 12.23\n");
			exit(0);
		}
		i++;
	}
	return (p);
}
