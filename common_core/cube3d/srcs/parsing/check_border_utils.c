/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:19 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/12 14:59:21 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_border_corner(t_map *map, int i, int j)
{
	int	tmp;
	int	len;

	tmp = 0;
	if (map->map[i][j] == '1' && map->map[i][j + 1] == '\0')
	{
		len = ft_strlen(map->map[i + 1]) - 1;
		tmp = j;
		while (map->map[i][tmp] == '1')
			tmp--;
		tmp++;
		if (tmp < len)
			tmp = len;
		if (map->map[i + 1][tmp] != '1')
			error("map error - border down");
		len = ft_strlen(map->map[i - 1]) - 1;
		tmp = j;
		while (map->map[i][tmp] == '1')
			tmp--;
		tmp++;
		if (tmp < len)
			tmp = len;
		if (map->map[i - 1][tmp] != '1')
			error("map error - border up");
	}
}

void	check_map_border_first_and_last_row(t_map *map, int i, int j)
{
	if (i == 0 || i == map->height - 1)
	{
		while (map->map[i][++j])
		{
			if (map->map[i][j] != '1')
				error("map error - border 1");
		}
	}
}

void	check_map_border_first_and_last(t_map *map, int i, int j)
{
	if (j == 0 || j == map->width - 1)
	{
		if (map->map[i][j] != '1')
			error("map error - border 2");
	}
}
