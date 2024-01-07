/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:08:33 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/01 17:19:17 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	parse_m(t_mlx mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 600)
	{
		while (y < 600)
		{
			mandelbrot(x, y, mlx);
			y++;
		}
		x++;
		y = 0;
	}
}

void	parse_j(t_mlx mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < 600)
	{
		while (y < 600)
		{
			julia(x, y, mlx);
			y++;
		}
		x++;
		y = 0;
	}
}
