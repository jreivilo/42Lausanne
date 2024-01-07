/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:25:58 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/12 16:32:49 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_color_floor_ceiling_iteration(char *line, int *i)
{
	while (ft_isdigit(line[*i]) == 1)
		(*i)++;
	if (line[*i] == ',')
		(*i)++;
}

int	check_color_floor_ceiling(char *line)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	while (line[i] != ' ' && line[i] != '\t')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_atoi(&line[i]) > 255 || ft_atoi(&line[i]) < 0)
		return (ERROR);
	check_color_floor_ceiling_iteration(line, &i);
	if (ft_atoi(&line[i]) > 255 || ft_atoi(&line[i]) < 0)
		return (ERROR);
	check_color_floor_ceiling_iteration(line, &i);
	if (ft_atoi(&line[i]) > 255 || ft_atoi(&line[i]) < 0)
		return (ERROR);
	while (ft_isdigit(line[i]) == 1)
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\0')
		return (ERROR);
	return (SUCCESS);
}

int	parse_color(char *line, t_map *map, int i)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	int		j;

	j = 0;
	if (check_color_floor_ceiling(line) == ERROR)
		error("Wrong color format");
	while (line[j] != ' ' && line[j] != '\t')
		j++;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	r = ft_atoi(&line[j]);
	parse_color_iteration(line, &j);
	g = ft_atoi(&line[j]);
	parse_color_iteration(line, &j);
	b = ft_atoi(&line[j]);
	if (i == 0)
		parse_color_init_color_floor(map, r, g, b);
	else if (i == 1)
		parse_color_init_color_ceiling(map, r, g, b);
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
	free(line);
	return (SUCCESS);
}
