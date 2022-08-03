/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 17:05:26 by jolivier          #+#    #+#             */
/*   Updated: 2022/08/01 17:05:28 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	modify_square(char **matrix, struct Square sq)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < sq.size)
	{
		j = 0;
		while (j < sq.size)
		{
			matrix[sq.row + i][sq.col + j] = 'X';
			j++;
		}
		i++;
	}
}

void	replace(char **matrix, struct s_info info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < info.ligne)
	{
		j = 0;
		while (j < info.colonne)
		{
			if (matrix[i][j] == 'X')
				matrix[i][j] = info.plein;
			j++;
		}
		i++;
	}
}

void	print_square(char **matrix, struct s_info info)
{
	int	j;

	j = 0;
	while (j < info.ligne)
	{
		write(1, matrix[j], info.colonne);
		write(1, "\n", 1);
		j++;
	}
}
