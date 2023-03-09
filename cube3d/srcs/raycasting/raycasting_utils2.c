/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:30:24 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 15:31:58 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_t_ray(t_all *all, t_ray *ray, int x, int y)
{
	(void)y;
	ray->ray_x = all->player->pos_x;
	ray->ray_y = all->player->pos_y;
	ray->ray_angle = (all->player->angle + \
		(((double)x / all->map->r_width) * 60) - 30 + 180) * M_PI / 180;
	ray->ray_x_step = sin(ray->ray_angle) * 0.001;
	ray->ray_y_step = cos(ray->ray_angle) * 0.001;
	ray->ray_length = 0;
	return (SUCCESS);
}
