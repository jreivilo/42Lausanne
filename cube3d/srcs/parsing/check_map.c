/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:59:13 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 16:47:43 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_char(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] != '0' && map->map[i][j] != '1'
				&& map->map[i][j] != '2' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'W' && map->map[i][j] != ' ')
				error("map error");
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_one_start(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		error("map error");
	return (SUCCESS);
}

int	check_map_border(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == 0 || i == map->height - 1)
			{
				if (map->map[i][j] != '1')
					error("map error");
			}
			else if (j == 0 || j == map->width - 1)
			{
				if (map->map[i][j] != '1')
					error("map error");
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_map(t_map *map)
{
	if (check_map_char(map) == ERROR)
		return (ERROR);
	if (check_map_border(map) == ERROR)
		return (ERROR);
	if (check_one_start(map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
