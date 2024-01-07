/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:15:17 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/17 12:50:42 by jolivier         ###   ########.fr       */
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
	map->wall = ft_calloc(sizeof(char *), 5 + 1);
	if (!(map->wall))
		error("Malloc error");
	map->wall[0] = NULL;
	map->wall[1] = NULL;
	map->wall[2] = NULL;
	map->wall[3] = NULL;
	map->wall[4] = NULL;
	map->width = 0;
	map->height = 0;
	map->r_height = 720;
	map->r_width = 1080;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->sprite = NULL;
	map->floor = 0;
	map->floor_set = 0;
	map->ceiling = 0;
	map->ceiling_set = 0;
	map->map_set = 0;
	map->map = NULL;
	return (SUCCESS);
}

int	init(t_map *map, t_player *player)
{
	(void)player;
	init_map(map);
	return (SUCCESS);
}

int	map_exist(t_map *map)
{
	if (map->width == 0 || map->height == 0)
		return (ERROR);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_map		map;
	t_player	player;

	if (argc != 2)
		return (ERROR);
	if (check_name_map(argv[1]) == ERROR)
		return (ERROR);
	init(&map, &player);
	if (parse_args(argv[1], &map) == ERROR)
		return (ERROR);
	if (is_not_map(&map) == ERROR)
		error("Not enough information");
	if (map_exist(&map) == ERROR)
		error("Map is not set or argugument after map");
	if (parse_player(&map, &player) == ERROR)
		return (ERROR);
	if (check_map(&map) == ERROR)
		return (ERROR);
	if (build_game(&map, &player) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
