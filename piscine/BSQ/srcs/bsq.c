/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 09:23:59 by hradoux           #+#    #+#             */
/*   Updated: 2022/08/03 15:52:35 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	norminette(int argc, int i)
{
	if (i < argc -1)
		write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_info	info;
	char	**tab2;

	if (argc == 1)
	{
		if (ft_pre_instruction_std_entry(&tab2, &info))
			solve_and_print(tab2, info);
		else
			write (1, "map error\n", 10);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_pre_instruction(&tab2, argv[i], &info))
		{
			solve_and_print(tab2, info);
			free_tab(tab2);
		}
		else
			write (1, "map error\n", 10);
		norminette(argc, i++);
	}
	return (0);
}
