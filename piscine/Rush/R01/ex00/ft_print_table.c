/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndiamant <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 14:27:10 by ndiamant          #+#    #+#             */
/*   Updated: 2022/07/24 15:16:56 by ndiamant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_print_table(int table[4][4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ft_putchar(table[i][j] % 10 + '0');
			if (j < 3)
			{
				ft_putchar(' ');
			}
			j++;
		}
		ft_putchar('\n');
		i++;
	}
}

/*int	main()
{
	int table[4][4] = {{1,2,3,4}, {1,2,3,4}, {1,2,3,4}, {1,2,3,4}};
	ft_print_table(table);
	return (0);
	
}*/
