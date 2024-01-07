/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:36:14 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/12 14:48:03 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color_iteration(char *line, int *j)
{
	while (ft_isdigit(line[*j]) == 1)
		(*j)++;
	(*j)++;
}

void	parse_color_init_color_floor(t_map *map, int r, int g, int b)
{
	map->floor = (r << 16) + (g << 8) + b;
	map->floor_set = 1;
}

void	parse_color_init_color_ceiling(t_map *map, int r, int g, int b)
{
	map->ceiling = (r << 16) + (g << 8) + b;
	map->ceiling_set = 1;
}
