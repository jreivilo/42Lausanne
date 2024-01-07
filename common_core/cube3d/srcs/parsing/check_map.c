/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:59:13 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/11 17:02:00 by nadel-be         ###   ########.fr       */
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
		while (map->map[i][j])
		{
			if (map->map[i][j] != '0' && map->map[i][j] != '1'
				&& map->map[i][j] != '2' && map->map[i][j] != 'N'
				&& map->map[i][j] != 'S' && map->map[i][j] != 'E'
				&& map->map[i][j] != 'W' && ft_isspace(map->map[i][j]) == 0)
			{
				printf("error au [%i][%i]: %c\n", i, j, map->map[i][j]);
				error("map error 1");
			}
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
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
		error("map error count player");
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
	add_protect(map);
	return (SUCCESS);
}
