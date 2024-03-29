/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:26:47 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/13 14:45:59 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_without_error(t_all *all)
{
	(void)all;
	exit(0);
	return (0);
}

int	awsd_hook(int keycode, t_all *all)
{
	if (keycode == 13)
		hook_up(all);
	if (keycode == 0)
		hook_left(all);
	if (keycode == 1)
		hook_down(all);
	if (keycode == 2)
		hook_right(all);
	return (0);
}

int	key_hook(int keycode, t_all *all)
{
	all->game->hook = 1;
	if (keycode == 53)
		exit(0);
	awsd_hook(keycode, all);
	if (keycode == 123)
	{
		all->player->angle += 5;
	}
	if (keycode == 124)
	{
		all->player->angle -= 5;
	}
	if (all->player->angle > 360)
		all->player->angle -= 360;
	if (all->player->angle < 0)
		all->player->angle += 360;
	return (ERROR);
}
