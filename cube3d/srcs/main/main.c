/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:15:17 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 16:42:26 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(0);
	return (ERROR);
}

int	init_map(t_map *map)
{
	map->width = 0;
	map->height = 0;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->sprite = NULL;
	map->floor = 0;
	map->ceiling = 0;
	map->map = NULL;
	return (SUCCESS);
}

int	init(t_map *map, t_player *player)
{
	(void)player;
	init_map(map);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;

	if (argc != 2)
		return (ERROR);
	init(&map, &player);
	if (parse_args(argv[1], &map) == ERROR)
		return (ERROR);
	if (parse_player(&map, &player) == ERROR)
		return (ERROR);
	if (check_map(&map) == ERROR)
		return (ERROR);
	if (build_game(&map, &player) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
