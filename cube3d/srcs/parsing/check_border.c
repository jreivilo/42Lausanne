/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_border.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:27:37 by nadel-be          #+#    #+#             */
/*   Updated: 2023/04/12 14:59:18 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_adjacent_up(t_map *map, int x, int y)
{
	int	len;

	len = ft_strlen(map->map[x - 1]) - 1;
	if (y > len)
		error("map error - space dead 1");
}

void	check_adjacent_down(t_map *map, int x, int y)
{
	int	len;

	len = ft_strlen(map->map[x + 1]) - 1;
	if (y > len)
		error("map error - space dead 2");
}

int	check_adjacent(t_map *map, int x, int y)
{
	check_adjacent_up(map, x, y);
	check_adjacent_down(map, x, y);
	return (SUCCESS);
}

int	check_map_border(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		if (i == 0 || i == map->height - 1)
			check_map_border_first_and_last_row(map, i, j);
		else
		{
			while (map->map[i][++j])
			{
				check_map_border_first_and_last(map, i, j);
				if (map->map[i][j] == '1' && map->map[i][j + 1] == '\0')
					check_map_border_corner(map, i, j);
				else
					if (map->map[i][j] == '0')
						check_adjacent(map, i, j);
			}
		}
	}
	return (SUCCESS);
}
