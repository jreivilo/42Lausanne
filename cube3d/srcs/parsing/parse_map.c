/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:05:18 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 16:41:16 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	realloc_map(t_map *map, char *line)
{
	char	**tmp;
	int		i;

	i = 0;
	if (map->width == 0 || map->width < (int)ft_strlen(line))
	{
		map->width = ft_strlen(line);
	}
	tmp = malloc(sizeof(char *) * (map->height + 1));
	if (!(tmp))
		error("Malloc error");
	while (i < map->height)
	{
		tmp[i] = map->map[i];
		i++;
	}
	tmp[i] = line;
	free(map->map);
	map->map = tmp;
	map->height++;
	return (SUCCESS);
}

int	parse_map_line(char *line, t_map *map)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!(tmp))
		error("Malloc error");
	while (line[i] != '\0')
	{
		if (line[i] == ' ' && line[i] == '\t')
			tmp[j] = 1;
		else
			tmp[j] = line[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	realloc_map(map, tmp);
	return (SUCCESS);
}
