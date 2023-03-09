/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:26:47 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 16:39:48 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	awsd_hook(int keycode, t_all *all)
{
	t_player	*player;

	player = all->player;
	if (keycode == 13)
	{
		player->pos_x += sin((player->angle + 180) * M_PI / 180) * 0.1;
		player->pos_y += cos((player->angle + 180) * M_PI / 180) * 0.1;
	}
	if (keycode == 1)
	{
		player->pos_x -= sin((player->angle + 180) * M_PI / 180) * 0.1;
		player->pos_y -= cos((player->angle + 180) * M_PI / 180) * 0.1;
	}
	if (keycode == 0)
	{
		player->pos_x += sin((player->angle + 90) * M_PI / 180) * 0.1;
		player->pos_y += cos((player->angle + 90) * M_PI / 180) * 0.1;
	}
	if (keycode == 2)
	{
		player->pos_x -= sin((player->angle + 90) * M_PI / 180) * 0.1;
		player->pos_y -= cos((player->angle + 90) * M_PI / 180) * 0.1;
	}
	return (0);
}

int	key_hook(int keycode, t_all *all)
{
	(void)(all);
	all->game->hook = 1;
	if (keycode == 53)
		exit(0);
	awsd_hook(keycode, all);
	if (keycode == 123)
	{
		all->player->angle -= 5;
	}
	if (keycode == 124)
	{
		all->player->angle += 5;
	}
	if (all->player->angle > 360)
		all->player->angle -= 360;
	if (all->player->angle < 0)
		all->player->angle += 360;
	return (ERROR);
}
