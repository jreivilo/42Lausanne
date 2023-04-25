/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:05:18 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/12 14:44:58 by jolivier         ###   ########.fr       */
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

int	true_len(char *line)
{
	int	i;
	int	t;

	i = 0;
	t = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			t += 4;
		i++;
	}
	t += ft_strlen(line);
	return (t);
}

int	parse_map_line(char *line, char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\t')
		{
			tmp[j++] = '1';
			tmp[j++] = '1';
			tmp[j++] = '1';
			tmp[j++] = '1';
			i++;
		}
		else if (line[i] == ' ')
		{
			tmp[j++] = '1';
			i++;
		}
		else
			tmp[j++] = line[i++];
	}
	return (SUCCESS);
}
