/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:43:39 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/11 11:27:05 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_resolution(char *line, t_map *map)
{
	int		i;

	i = 0;
	while (ft_isdigit(line[i]) != 1)
		i++;
	map->r_width = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]) == 1)
		i++;
	map->r_height = ft_atoi(&line[i]);
	if (map->r_width > 2560)
		map->r_width = 2560;
	if (map->r_height > 1440)
		map->r_height = 1440;
	free(line);
	return (SUCCESS);
}
