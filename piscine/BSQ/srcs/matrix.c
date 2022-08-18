/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hradoux <marvin@42lausannmarvin@42lausa    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:06:03 by hradoux           #+#    #+#             */
/*   Updated: 2022/08/02 20:40:42 by hradoux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

char	*ft_file_to_buffer(char *file)
{
	int		fd;
	int		count;
	int		size;
	char	*tab;

	tab = malloc((ft_tot_length_file(file) + 1) * sizeof(char));
	if (!tab)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	size = 1;
	while (size > 0)
	{
		size = read(fd, &tab[count], 150);
		count = count + size;
	}
	close(fd);
	tab[count + size] = 0;
	return (tab);
}

char	*ft_file_to_buffer_std_entry(void)
{
	int		size;
	char	*tab;
	char	buffer[1024];

	tab = malloc(1 * sizeof(char));
	if (!tab)
		return (0);
	size = 1;
	while (size > 0)
	{
		size = read(0, buffer, 1024);
		if (size > 0)
			tab = ft_active_malloc(tab, buffer, size);
	}
	return (tab);
}

char	*ft_active_malloc(char *tab, char *buffer, int size)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc ((ft_strlen(tab) + size + 1) * sizeof(char));
	if (!tmp)
		return (0);
	i = 0;
	while (tab[i])
	{
		tmp[i] = tab[i];
		i++;
	}
	tmp[i] = 0;
	i = 0;
	j = ft_strlen(tab);
	while (buffer[i] && i < size)
	{
		tmp[i + j] = buffer[i];
		i++;
	}
	tmp[j + i] = 0;
	free(tab);
	return (tmp);
}

void	solve_and_print(char **matrix, struct s_info info)
{
	t_square	result;

	if (info.case_0 == 1)
	{
		write(1, "\n", 1);
		return ;
	}
	result = solver(matrix, info);
	modify_square(matrix, result);
	if (result.size > 0)
	{
		replace(matrix, info);
	}
	print_square(matrix, info);
}
