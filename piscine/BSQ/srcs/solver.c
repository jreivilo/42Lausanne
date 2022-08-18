/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:08:49 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/03 15:40:07 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	row_condition(t_square sq, char **matrix, char stop_square);
int	col_condition(t_square sq, char **matrix, char stop_square);

struct Square	if_add_result(struct Square sq, struct Square result)
{
	if (sq.size > result.size)
	{
		result.size = sq.size;
		result.col = sq.col;
		result.row = sq.row;
	}
	return (result);
}

t_square	solver(char **matrix, struct s_info info)
{
	t_square	sq;
	t_square	result;

	sq.row = 0;
	sq.size = 1;
	result.size = 0;
	while (sq.row < info.ligne - result.size)
	{
		sq.col = 0;
		while (sq.col < info.colonne - result.size)
		{
			while ((sq.col + sq.size - 1) < info.colonne
				&& (sq.row + sq.size - 1) < info.ligne
				&& row_condition(sq, matrix, info.obstacle) == 1
				&& col_condition(sq, matrix, info.obstacle) == 1)
			{
				result = if_add_result(sq, result);
				sq.size++;
			}
			sq.size = sq.size - 1;
			sq.col++;
		}
		sq.row++;
	}
	return (result);
}
