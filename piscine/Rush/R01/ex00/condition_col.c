/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_col.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 15:05:44 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/24 15:05:51 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	norminette_count_up(int table[4][4], int col)
{
	char	countup;
	int		i;
	int		tmp;

	i = 0;
	countup = '1';
	tmp = table[i][col];
	i++;
	while (i < 4)
	{
		if (tmp < table[i][col])
		{
			tmp = table[i][col];
			countup++;
		}
		i++;
	}
	return (countup);
}

char	norminette_count_down(int table[4][4], int col)
{
	char	countdown;
	int		i;
	int		tmp;

	countdown = '1';
	i = 3;
	tmp = table[i][col];
	i--;
	while (i >= 0)
	{
		if (tmp < table[i][col])
		{
			tmp = table[i][col];
			countdown++;
		}
		i--;
	}
	return (countdown);
}

int	c_col(char **argv, int table[4][4], int col)
{
	char	countup;
	char	countdown;

	countup = norminette_count_up(table, col);
	countdown = norminette_count_down(table, col);
	if (argv[1][0 + col * 2] == countup && argv[1][8 + col * 2] == countdown)
		return (1);
	else
		return (0);
}
