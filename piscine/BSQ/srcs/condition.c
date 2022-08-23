/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:06:08 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/01 17:06:09 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	col_condition(t_square sq, char **matrix, char stop_square)
{
	int	i;

	i = 0;
	sq.size--;
	while (i <= sq.size)
	{
		if (matrix[sq.row + sq.size - i][sq.col + sq.size] == stop_square)
			return (0);
		i++;
	}
	return (1);
}

int	row_condition(t_square sq, char **matrix, char stop_square)
{
	int	i;

	i = 0;
	sq.size--;
	while (i <= sq.size)
	{
		if (matrix[sq.row + sq.size][sq.col + sq.size - i] == stop_square)
			return (0);
		i++;
	}
	return (1);
}
