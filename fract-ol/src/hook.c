/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:34:20 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/01 17:49:55 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	(void) x;
	(void) y;
	if (button == 4)
	{
		mlx->zoom += 1.1;
		mlx->max_iter = mlx->max_iter + mlx->zoom;
		if (mlx->max_iter >= 100)
			mlx->max_iter = 500;
	}
	if (button == 5)
	{
		mlx->zoom /= 1.1;
		mlx->max_iter = mlx->max_iter - mlx->zoom;
		if (mlx->max_iter <= 20)
			mlx->max_iter = 20;
	}
	return (0);
}

int	close_windows(t_mlx *mlx)
{
	(void) mlx;
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_mlx *mlx)
{
	(void) mlx;
	if (keycode == 53)
	{
		exit(0);
	}
	return (0);
}
