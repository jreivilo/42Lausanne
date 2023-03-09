/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_resolution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:43:39 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 16:29:28 by jolivier         ###   ########.fr       */
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
	return (SUCCESS);
}
