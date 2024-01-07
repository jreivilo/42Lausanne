/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 16:23:04 by nadel-be          #+#    #+#             */
/*   Updated: 2023/04/17 12:50:57 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_pos(t_all *all, int x, int y)
{
	if (all->map->map[(int)y][(int)x] == '1' \
		|| all->map->map[(int)y][(int)x] == '2')
		return (ERROR);
	return (SUCCESS);
}

int	hook_up(t_all *all)
{
	t_player	*player;
	double		new_pos_x;
	double		new_pos_y;

	player = all->player;
	new_pos_x = player->pos_x + sin((player->angle + 180) * M_PI / 180) * 0.1;
	new_pos_y = player->pos_y + cos((player->angle + 180) * M_PI / 180) * 0.1;
	if (check_pos(all, new_pos_x, new_pos_y) == SUCCESS)
	{
		player->pos_x = new_pos_x;
		player->pos_y = new_pos_y;
	}
	return (SUCCESS);
}

int	hook_down(t_all *all)
{
	t_player	*player;
	double		new_pos_x;
	double		new_pos_y;

	player = all->player;
	new_pos_x = player->pos_x - sin((player->angle + 180) * M_PI / 180) * 0.1;
	new_pos_y = player->pos_y - cos((player->angle + 180) * M_PI / 180) * 0.1;
	if (check_pos(all, new_pos_x, new_pos_y) == SUCCESS)
	{
		player->pos_x = new_pos_x;
		player->pos_y = new_pos_y;
	}
	return (SUCCESS);
}

int	hook_left(t_all *all)
{
	t_player	*player;
	double		new_pos_x;
	double		new_pos_y;

	player = all->player;
	new_pos_x = player->pos_x - sin((player->angle + 90) * M_PI / 180) * 0.1;
	new_pos_y = player->pos_y - cos((player->angle + 90) * M_PI / 180) * 0.1;
	if (check_pos(all, new_pos_x, new_pos_y) == SUCCESS)
	{
		player->pos_x = new_pos_x;
		player->pos_y = new_pos_y;
	}
	return (SUCCESS);
}

int	hook_right(t_all *all)
{
	t_player	*player;
	double		new_pos_x;
	double		new_pos_y;

	player = all->player;
	new_pos_x = player->pos_x + sin((player->angle + 90) * M_PI / 180) * 0.1;
	new_pos_y = player->pos_y + cos((player->angle + 90) * M_PI / 180) * 0.1;
	if (check_pos(all, new_pos_x, new_pos_y) == SUCCESS)
	{
		player->pos_x = new_pos_x;
		player->pos_y = new_pos_y;
	}
	return (SUCCESS);
}
