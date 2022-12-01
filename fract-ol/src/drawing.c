/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:04:56 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/01 17:37:30 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	get_color(t_mlx	*mlx)
{
	mlx->co[0] = 800;
	mlx->co[1] = 200;
	mlx->co[2] = 300;
	mlx->co[3] = 400;
	mlx->co[4] = 500;
	mlx->co[5] = 600;
	mlx->co[6] = 700;
	mlx->co[7] = 800;
	mlx->co[8] = 900;
	mlx->co[9] = 1000;
}

void	mandelbrot(int cor_x, int cor_y, t_mlx mlx)
{
	t_frac	frac;
	double	iteration;

	frac.x0 = ((cor_x + mlx.x) / 400.0 * 2.0 - 2.25) / mlx.zoom;
	frac.y0 = ((cor_y + mlx.y) / 400.0 * 2.0 - 1.5) / mlx.zoom;
	frac.xtemp = 0;
	frac.x = 0;
	frac.y = 0;
	iteration = 0;
	while (frac.x * frac.x + frac.y * frac.y < 4 && iteration < mlx.max_iter)
	{
		frac.xtemp = frac.x * frac.x - frac.y * frac.y + frac.x0;
		frac.y = 2 * frac.x * frac.y + frac.y0;
		frac.x = frac.xtemp;
		iteration++;
	}
	if (iteration == mlx.max_iter)
		my_mlx_pixel_put(&mlx, cor_x, cor_y, 0X000000);
	else
		my_mlx_pixel_put(&mlx, cor_x, cor_y, (mlx.co)[(int)iteration % 10]);
}

void	julia(int cor_x, int cor_y, t_mlx mlx)
{
	t_frac	frac;
	double	iteration;

	frac.x0 = (cor_x / 400.0 * 3.0 - 2.5) / mlx.zoom;
	frac.y0 = (cor_y / 400.0 * 2.0 - 1.5) / mlx.zoom;
	frac.xtemp = 0;
	frac.x = frac.x0;
	frac.y = frac.y0;
	iteration = 0;
	while (frac.x * frac.x + frac.y * frac.y < 4 && iteration < mlx.max_iter)
	{
		frac.xtemp = frac.x * frac.x - frac.y * frac.y + mlx.julia_x;
		frac.y = 2 * frac.x * frac.y + mlx.julia_y;
		frac.x = frac.xtemp;
		iteration++;
	}
	if (iteration == mlx.max_iter)
		my_mlx_pixel_put(&mlx, cor_x, cor_y, 0X000000);
	else
		my_mlx_pixel_put(&mlx, cor_x, cor_y, (mlx.co)[(int)iteration % 10]);
}
