/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:20:44 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/13 13:26:03 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_side_wall(t_all *all, t_ray *ray)
{
	if ((int)ray->ray_x == (int)(ray->ray_x - ray->ray_x_step))
	{
		if ((int)ray->ray_y > (int)(ray->ray_y - ray->ray_y_step))
			all->info->side = NORTH;
		else
			all->info->side = SOUTH;
	}
	if ((int)ray->ray_y == (int)(ray->ray_y - ray->ray_y_step))
	{
		if ((int)ray->ray_x > (int)(ray->ray_x - ray->ray_x_step))
			all->info->side = WEST;
		else
			all->info->side = EAST;
	}
	return (SUCCESS);
}

int	get_side_ratio(t_all *all, t_ray *ray)
{
	if ((int)ray->ray_x == (int)(ray->ray_x - ray->ray_x_step))
	{
		if ((int)ray->ray_y > (int)(ray->ray_y - ray->ray_y_step))
			all->info->side_ratio = \
				(ray->ray_x - (double)floor(ray->ray_x));
		else
			all->info->side_ratio = \
				1 - (ray->ray_x - (double)floor(ray->ray_x));
	}
	else
	{
		if ((int)ray->ray_x > (int)(ray->ray_x - ray->ray_x_step))
			all->info->side_ratio = \
				1 + ((double)floor(ray->ray_y) - ray->ray_y);
		else
			all->info->side_ratio = \
				1 - ((double)ceil(ray->ray_y) - ray->ray_y);
	}
	return (SUCCESS);
}

double	calculate_distance_to_wall(t_all *all, int x, int y)
{
	t_ray	ray;
	int		hit_wall;

	init_t_ray(all, &ray, x, y);
	(void)y;
	hit_wall = 0;
	while (hit_wall == 0)
	{
		ray.ray_x += ray.ray_x_step;
		ray.ray_y += ray.ray_y_step;
		ray.ray_length += 1;
		if (all->map->map[(int)ray.ray_y][(int)ray.ray_x] == '1' \
			|| all->map->map[(int)ray.ray_y][(int)ray.ray_x] == '2')
		{
			hit_wall = 1;
			if (all->map->map[(int)ray.ray_y][(int)ray.ray_x] == '2')
				all->info->sprite = 1;
			else
				all->info->sprite = 0;
		}
	}
	get_side_wall(all, &ray);
	get_side_ratio(all, &ray);
	return ((ray.ray_length * cos((all->player->angle * M_PI / 180) \
		- ray.ray_angle)) * 0.001);
}

int	col_pix(t_all *all, double ratio, double side_ratio, int type)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;

	ratio = 1 - ratio;
	if (side_ratio < 0)
		side_ratio = 0;
	if (ratio > 1)
		ratio = 1;
	if (ratio < 0)
		ratio = 0;
	r = all->texture[type].addr[(int)(ratio * all->texture[type].width) \
		* all->texture[type].line_length \
			+ (int)(side_ratio * all->texture[type].height) \
				* (all->texture[type].bits_per_pixel / 8)];
	g = all->texture[type].addr[(int)(ratio * all->texture[type].width) \
		* all->texture[type].line_length \
			+ (int)(side_ratio * all->texture[type].height) \
				* (all->texture[type].bits_per_pixel / 8) + 1];
	b = all->texture[type].addr[(int)(ratio * all->texture[type].width) \
		* all->texture[type].line_length \
			+ (int)(side_ratio * all->texture[type].height) \
				* (all->texture[type].bits_per_pixel / 8) + 2];
	return (rgb_to_hex(r, g, b));
}

int	raycasting(t_all *all)
{
	int		x;
	int		y;
	double	distance;
	t_game	*game;

	x = 0;
	game = all->game;
	if (all->game->hook == 0)
		return (SUCCESS);
	while (x < all->map->r_width)
	{
		y = 0;
		distance = calculate_distance_to_wall(all, all->map->r_width - x, y);
		if (distance < 0)
			distance = -distance;
		while (y < all->map->r_height)
		{
			display_pixel(all, x, y, distance);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	all->game->hook = 0;
	return (SUCCESS);
}
