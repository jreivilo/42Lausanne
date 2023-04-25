/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:13:24 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/12 14:29:20 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return (b << 16 | g << 8 | r);
}

int	display_sky(t_all *all, int x, int y)
{
	pixel_put(all->game, x, y, all->map->ceiling);
	return (SUCCESS);
}

int	display_floor(t_all *all, int x, int y)
{
	pixel_put(all->game, x, y, all->map->floor);
	return (SUCCESS);
}

int	display_wall(t_all *all, int x, int y, double ratio)
{
	double	side_ratio;

	side_ratio = all->info->side_ratio;
	if (ratio == 0)
		ratio = 0.0001;
	if (ratio == 1)
		ratio = 0.9999;
	if (all->info->sprite == 1)
	{
		pixel_put(all->game, x, y, col_pix(all, ratio, side_ratio, SPRITE));
		return (SUCCESS);
	}
	if (all->info->side == NORTH)
		pixel_put(all->game, x, y, col_pix(all, ratio, side_ratio, NORTH));
	else if (all->info->side == SOUTH)
		pixel_put(all->game, x, y, col_pix(all, ratio, side_ratio, SOUTH));
	else if (all->info->side == WEST)
		pixel_put(all->game, x, y, col_pix(all, ratio, side_ratio, WEST));
	else if (all->info->side == EAST)
		pixel_put(all->game, x, y, col_pix(all, ratio, side_ratio, EAST));
	return (SUCCESS);
}

int	display_pixel(t_all *all, int x, int y, double distance)
{
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	double	ratio;

	wall_height = (all->map->r_height / distance);
	wall_top = (all->map->r_height / 2) - (wall_height / 2);
	wall_bottom = (all->map->r_height / 2) + (wall_height / 2);
	ratio = - (y - wall_bottom) / (wall_height);
	if (y < wall_top)
		display_sky(all, x, y);
	else if (y > wall_bottom)
		display_floor(all, x, y);
	else if (y >= wall_top && y <= wall_bottom)
		display_wall(all, x, y, ratio);
	return (SUCCESS);
}
