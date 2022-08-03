/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkchain.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfinocie <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:05:23 by vfinocie          #+#    #+#             */
/*   Updated: 2022/07/24 19:10:07 by vfinocie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>	

void	error(void)
{
	write(1, "Error", 5);
	write(1, "\n", 1);
}

int	check_one(char **argv, int i)
{
	if (argv[1][i + 1] == 0 || argv[1][i + 1] == ' ')
		i++;
	else
	{
		error();
		return (-1);
	}
	return (i);
}

int	check_two(char **argv, int i)
{
	if (argv[1][i] == ' ')
	{
		if (argv[1][i + 1] > '0' && argv[1][i + 1] < '5')
			i++;
		else
		{
			error();
			return (-1);
		}
	}
	if (argv[1][i] < '1' || argv[1][i] > '4')
	{
		error();
		return (-1);
	}
	return (i);
}

char	checkchain(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
	{
		error();
		return (-1);
	}
	while (argv[1][i] != 0 && i >= 0)
	{
		if (argv[1][i] > '0' && argv[1][i] < '5')
			i = check_one(argv, i);
		else
			i = check_two(argv, i);
	}
	if (i != 31 && i != -1)
	{
		error();
		return (-5);
	}
	if (i < 0)
		return (-1);
	else
		return (0);
}
