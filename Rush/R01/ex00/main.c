/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 16:20:07 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/24 16:20:09 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	checkchain(int argc, char **argv);

int		c_nbr_row(int table[4][4], int row);

int		c_nbr_col(int table[4][4], int col);

int		c_row(char **argv, int table[4][4], int row);

int		c_col(char **argv, int table[4][4], int col);

void	ft_print_table(int table[4][4]);

void	init(int *table_int)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		table_int[i] = 1234;
		i++;
	}
}

void	i_append(int table[4][4], int nbr, int row)
{
	table[row][0] = (nbr / 10 / 10 / 10 % 10);
	table[row][1] = (nbr / 10 / 10 % 10);
	table[row][2] = (nbr / 10 % 10);
	table[row][3] = (nbr % 10);
}

void	i_row(char **argv, int table[4][4], int *table_int, int row)
{
	while (row < 4 && table_int[0] < 4322)
	{
		i_append(table, table_int[row], row);
		while (!(c_row(argv, table, row) == 1 && c_nbr_row(table, row) == 1))
		{
			if (table_int[0] == 4322)
			{
				break ;
			}
			if (table_int[row] > 4321)
			{
				table_int[row] = 1234;
				table_int[row - 1] = table_int[row - 1] + 1;
				row = row - 1;
			}
			table_int[row] = table_int[row] + 1;
			i_append(table, table_int[row], row);
		}
		row = row + 1;
	}
}

void	i_col(char **argv, int table[4][4], int *table_int, int row)
{
	int	col;

	col = 0;
	while (col < 4 && table_int[0] < 4322)
	{
		while (!(c_col(argv, table, col) == 1 && c_nbr_col(table, col) == 1))
		{
			if (table_int[0] == 4322)
			{
				break ;
			}
			table_int[row] = table_int[row] + 1;
			i_row(argv, table, table_int, row);
			col = 0;
		}
		col++;
	}	
}

int	main(int argc, char **argv)
{
	int	col;
	int	row;
	int	table[4][4];
	int	table_int[4];

	col = 0;
	(void)argc;
	if (checkchain(argc, argv) == 0)
	{
		init(table_int);
		i_row(argv, table, table_int, 0);
		row = 3;
		i_col(argv, table, table_int, row);
		if (table_int[0] < 4322)
		{
			ft_print_table(table);
		}
		else
			write (1, "Error\n", 6);
	}
}
