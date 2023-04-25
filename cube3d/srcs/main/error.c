/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 16:59:26 by nadel-be          #+#    #+#             */
/*   Updated: 2023/04/12 15:09:57 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_with_free(t_map *map, char *str)
{
	int	i;

	i = 0;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	while (map->map[i])
	{
		free(map->map[i]);
	}
	free(map->map);
	exit(0);
}
