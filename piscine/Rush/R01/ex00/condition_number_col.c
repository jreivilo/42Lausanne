/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_number_col.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:07:13 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/24 15:07:21 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	c_nbr_col(int table[4][4], int col)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (i < 4)
	{
		if (!(1 <= table[i][col] && table[i][col] <= 4))
			return (0);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		tmp = table[i][col];
		j = i + 1;
		while (j < 4)
		{
			if (table[j][col] == tmp)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
