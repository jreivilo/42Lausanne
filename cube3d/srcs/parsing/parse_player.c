/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:10:27 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/17 12:48:04 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_direction(t_map *map, t_player *player, int i, int j)
{
	if (map->map[i][j] == 'N')
		player->angle = 0;
	else if (map->map[i][j] == 'S')
		player->angle = 180;
	else if (map->map[i][j] == 'E')
		player->angle = 270;
	else if (map->map[i][j] == 'W')
		player->angle = 90;
	return (SUCCESS);
}

int	parse_player(t_map *map, t_player *player)
{
	int		i;
	int		j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				player->pos_x = j + 0.5;
				player->pos_y = i + 0.5;
				check_direction(map, player, i, j);
				return (SUCCESS);
			}
			j++;
		}
		i++;
	}
	error_with_free(map, "error map - missing player");
	return (ERROR);
}
