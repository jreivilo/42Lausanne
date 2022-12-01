/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:09:29 by jolivier          #+#    #+#             */
/*   Updated: 2022/11/17 16:56:06 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strlen_dot(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '.')
		i++;
	return (i);
}

void	get_variable_value(t_atoi_double *atoi_d, char *argv)
{
	atoi_d->i = 0;
	atoi_d->j = 1;
	atoi_d->j_arg = 0;
	atoi_d->len_total = ft_strlen(argv);
	atoi_d->len_dot = ft_strlen_dot(argv);
	atoi_d->diff = atoi_d->len_dot;
}

int	get_julia_arg_before_point(t_atoi_double *a_d, char *argv)
{
	int	minus;

	minus = 0;
	if (argv[a_d->i] == '-')
	{
		minus = 1;
		a_d->i++;
		a_d->diff--;
	}
	while (a_d->diff > 0)
	{
		a_d->j_arg += (double)(argv[a_d->i] - '0') * pow(10, a_d->diff) / 10;
		a_d->diff--;
		a_d->i++;
	}
	return (minus);
}

double	get_julia_arg(char *argv)
{
	t_atoi_double	atoi_d;
	int				minus;

	get_variable_value(&atoi_d, argv);
	minus = get_julia_arg_before_point(&atoi_d, argv);
	atoi_d.diff = atoi_d.len_total - atoi_d.len_dot - 1;
	atoi_d.i++;
	while (atoi_d.diff > 0)
	{
		if (argv[atoi_d.i] == '0')
		{
			atoi_d.j++;
			atoi_d.i++;
		}
		else
		{
			atoi_d.j_arg += (double)(argv[atoi_d.i] - '0') / pow(10, atoi_d.j);
			atoi_d.j++;
			atoi_d.i++;
		}
		atoi_d.diff--;
	}
	if (minus == 1)
		atoi_d.j_arg *= -1;
	return (atoi_d.j_arg);
}
