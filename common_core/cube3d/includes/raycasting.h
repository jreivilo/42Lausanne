/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:21:10 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 15:49:49 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H

# include "cub3d.h"

int	init_t_ray(t_all *all, t_ray *ray, int x, int y);

int	raycasting(t_all *all);
int	col_pix(t_all *all, double ratio, double side_ratio, int type);

int	rgb_to_hex(int r, int g, int b);

int	display_pixel(t_all *all, int x, int y, double distance);

#endif