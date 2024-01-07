/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_protect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:34:18 by nadel-be          #+#    #+#             */
/*   Updated: 2023/04/11 16:25:30 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	max_width(t_map *map)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (i < map->height)
	{
		if ((int)ft_strlen(map->map[i]) > nb)
			nb = (int)ft_strlen(map->map[i]);
		i++;
	}
	return (nb);
}

void	change_space(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == ' ')
				map->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

void	add_wall(t_map *map, int max)
{
	int		i;
	char	*new;
	int		len;

	i = 0;
	while (i < map->height)
	{
		len = (int)ft_strlen(map->map[i]);
		if (len < max)
		{
			new = ft_calloc(sizeof(*new), (max + 1));
			if (!(new))
				error("Malloc error");
			ft_memset(new, '1', max);
			ft_memcpy(new, map->map[i], len);
			free(map->map[i]);
			map->map[i] = new;
		}
		i++;
	}
}

void	add_protect(t_map *map)
{
	int	max;

	max = max_width(map);
	change_space(map);
	add_wall(map, max);
}
