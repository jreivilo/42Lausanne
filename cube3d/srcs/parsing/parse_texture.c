/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:25:58 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 11:52:00 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_color(char *line, t_map *map, int i)
{
	int		j;
	int		k;
	char	*tmp;

	j = 0;
	k = 0;
	while (line[j] != ' ' && line[j] != '\t')
		j++;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	tmp = ft_substr(line, j, ft_strlen(line) - j);
	if (i == 0)
		map->floor = ft_atoi(tmp);
	else if (i == 1)
		map->ceiling = ft_atoi(tmp);
	free(tmp);
	return (SUCCESS);
}

int	parse_texture(char *line, t_map *map, int i)
{
	int		j;

	j = 0;
	while (line[j] != ' ' && line[j] != '\t')
		j++;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (i == 0)
		map->wall[0] = ft_strdup(&line[j]);
	else if (i == 1)
		map->wall[1] = ft_strdup(&line[j]);
	else if (i == 2)
		map->wall[2] = ft_strdup(&line[j]);
	else if (i == 3)
		map->wall[3] = ft_strdup(&line[j]);
	else if (i == 4)
		map->wall[4] = ft_strdup(&line[j]);
	return (SUCCESS);
}
