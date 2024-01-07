/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:30:40 by nadel-be          #+#    #+#             */
/*   Updated: 2023/04/17 12:49:40 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_not_map(t_map *map)
{
	if (map->floor_set == 0 || map->ceiling_set == 0
		|| map->wall[0] == NULL || map->wall[1] == NULL
		|| map->wall[2] == NULL || map->wall[3] == NULL
		|| map->wall[4] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_isspace(int c)
{
	if (c == ' '
		|| c == '\t' || c == '\v' || c == '\n' || c == '\r' || c == '\f')
		return (1);
	return (0);
}

char	*ft_trim(char *line)
{
	char	*res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = ft_calloc(sizeof(*res), ft_strlen(line) + 1);
	if (!(res))
		error("Malloc error");
	while (line[i] && ft_isspace(line[i]) == 1)
		i++;
	while (line[i])
	{
		res[j] = line[i];
		j++;
		i++;
	}
	return (res);
}
