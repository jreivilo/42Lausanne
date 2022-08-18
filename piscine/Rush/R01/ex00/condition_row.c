/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_row.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:42:22 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/24 14:42:53 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
char	norminette_count_left(int table[4][4], int row)
{
	char	count_l;
	int		i;
	int		tmp;

	i = 0;
	count_l = '1';
	tmp = table[row][i];
	i++;
	while (i < 4)
	{
		if (tmp < table[row][i])
		{
			tmp = table[row][i];
			count_l++;
		}
		i++;
	}
	return (count_l);
}

char	norminette_count_right(int table[4][4], int row)
{
	char	count_r;
	int		i;
	int		tmp;

	count_r = '1';
	i = 3;
	tmp = table[row][i];
	i--;
	while (i >= 0)
	{
		if (tmp < table[row][i])
		{
			tmp = table[row][i];
			count_r++;
		}
		i--;
	}
	return (count_r);
}

int	c_row(char **argv, int table[4][4], int row)
{
	char	count_l;
	char	count_r;

	count_l = norminette_count_left(table, row);
	count_r = norminette_count_right(table, row);
	if (argv[1][16 + row * 2] == count_l && argv[1][24 + row * 2] == count_r)
		return (1);
	else
		return (0);
}
