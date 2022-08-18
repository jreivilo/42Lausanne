/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_number_row.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 19:16:32 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/23 19:16:34 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	c_nbr_row(int table[4][4], int row)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < 4)
	{
		if (!(1 <= table[row][i] && table[row][i] <= 4))
			return (0);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		tmp = table[row][i];
		j = i + 1;
		while (j < 4)
		{
			if (table[row][j] == tmp)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
