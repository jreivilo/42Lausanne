/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:41:47 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/11 16:15:06 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	return (0);
}

int	init_all(t_all *all, t_game *game, t_info *info, t_texture *texture)
{
	int	i;

	all->game = game;
	all->texture = texture;
	all->info = info;
	all->game->hook = 1;
	all->info->sprite = 0;
	i = 0;
	while (i < 5)
	{
		all->texture[i].img = mlx_xpm_file_to_image(all->game->mlx, \
			all->map->wall[i], &all->texture[i].width, &all->texture[i].height);
		if (all->texture[i].img == NULL)
			error("Texture not found");
		all->texture[i].addr = mlx_get_data_addr(all->texture[i].img, \
			&all->texture[i].bits_per_pixel, &all->texture[i].line_length, \
				&all->texture[i].endian);
		i++;
	}
	return (SUCCESS);
}

int	build_game(t_map *map, t_player *player)
{
	t_game		game;
	t_all		all;
	t_info		info;
	t_texture	texture[5];

	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, map->r_width, map->r_height, "Cub3D");
	game.img = mlx_new_image(game.mlx, map->r_width, map->r_height);
	game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel, &\
		game.line_length, &game.endian);
	all.player = player;
	all.map = map;
	init_all(&all, &game, &info, texture);
	raycasting(&all);
	mlx_hook(game.win, 17, 0, exit_without_error, &all);
	mlx_hook(game.win, 2, 0, key_hook, &all);
	mlx_loop_hook(game.mlx, raycasting, &all);
	mlx_put_image_to_window(game.mlx, game.win, game.img, 0, 0);
	mlx_loop(game.mlx);
	return (SUCCESS);
}
