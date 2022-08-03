/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:54:26 by hradoux           #+#    #+#             */
/*   Updated: 2022/08/03 12:06:56 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int	ft_tot_length_file(char *file)
{
	int		fd;
	int		count;
	char	c;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	count = 0;
	while (read(fd, &c, 1))
	{
		count++;
	}
	close(fd);
	return (count);
}

int	ft_check_info(t_info *info, char *tab)
{
	int	i;

	i = 0;
	while (tab[i] && tab[i] != '\n')
		i++;
	if (i < 4)
		return (0);
	info->case_0 = 0;
	info->ligne = ft_atoi(tab, i - 3);
	info->size_file = ft_strlen(tab);
	info->vide = tab[i - 3];
	info->obstacle = tab[i - 2];
	info->plein = tab[i - 1];
	if (info->vide == info->obstacle || info->vide == info->plein
		|| info->obstacle == info->plein)
		return (0);
	if (info->ligne == 0)
	{	
		info->case_0 = 1;
		return (1);
	}
	info->colonne = (info->size_file - 5 - info->ligne) / info->ligne;
	return (1);
}

int	ft_check_map(char *str, t_info *info)
{
	int		i;
	int		size_colonne;

	i = 0;
	while (str[i])
	{
		size_colonne = 0;
		while (str[i] != 10 && str[i])
		{
			if (str[i] != info->vide && str[i] != info->obstacle)
				return (0);
			i++;
			size_colonne++;
		}
		if (size_colonne != info->colonne)
			return (0);
		i++;
	}
	if (i != info->ligne * (info->colonne + 1))
		return (0);
	return (1);
}

int	ft_pre_instruction_std_entry(char ***tab2, t_info *info)
{
	int		j;
	int		check;
	char	*tab1;

	check = 0;
	tab1 = ft_file_to_buffer_std_entry();
	if (tab1 != 0)
	{
		if (ft_check_info(info, tab1))
		{
			j = 0;
			while (tab1[j] && tab1[j] != '\n')
				j++;
			j++;
			if (ft_check_map(tab1 + j, info))
			{	
				*tab2 = ft_split(tab1 + j, "\n");
				check = 1;
			}
		}
	}
	free(tab1);
	return (check);
}

int	ft_pre_instruction(char ***tab2, char *argv, t_info *info)
{
	int		j;
	int		check;
	char	*tab1;

	check = 0;
	tab1 = ft_file_to_buffer(argv);
	if (tab1 != 0)
	{
		if (ft_check_info(info, tab1))
		{
			j = 0;
			while (tab1[j] && tab1[j] != '\n')
				j++;
			j++;
			if (ft_check_map(tab1 + j, info))
			{	
				*tab2 = ft_split(tab1 + j, "\n");
				check = 1;
			}
		}
	}
	free(tab1);
	return (check);
}
