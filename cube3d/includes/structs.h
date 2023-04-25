/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:56:09 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/17 11:36:52 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "cub3d.h"

typedef struct game
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		hook;
}	t_game;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		orientation;
	double		angle;
}	t_player;

typedef struct texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_map
{
	char	**map;
	double	r_width;
	double	r_height;
	int		width;
	int		height;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	char	**wall;
	int		floor;
	int		floor_set;
	int		ceiling;
	int		ceiling_set;
	int		map_set;
}	t_map;

typedef struct s_info
{
	int		side;
	double	side_ratio;
	int		sprite;
}	t_info;

typedef struct s_all
{
	t_map		*map;
	t_player	*player;
	t_game		*game;
	t_texture	*texture;
	t_info		*info;
}	t_all;

typedef struct s_ray
{
	double		ray_angle;
	double		ray_x;
	double		ray_y;
	double		ray_x_step;
	double		ray_y_step;
	double		ray_length;
}	t_ray;

#endif