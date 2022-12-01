/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:25:17 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/01 17:55:42 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i])
		return (0);
	return (1);
}

void	check_args(int argc, char**argv)
{
	if (argc == 1)
	{
		ft_putstr("Error: No argument\n");
		ft_putstr("Correct arguments : mandelbrot, julia\n");
		exit(0);
	}
	if (ft_strcmp(argv[1], "mandelbrot") != 0
		&& ft_strcmp(argv[1], "julia") != 0)
	{
		ft_putstr("Error: Wrong name\n");
		ft_putstr("Try mandelbrot or julia\n");
		exit(0);
	}
	if (ft_strcmp(argv[1], "mandelbrot") == 0 && argc != 2)
	{
		ft_putstr("Error: mandelbrot don't require any aditional arguments\n");
		exit(0);
	}
	if (ft_strcmp(argv[1], "julia") == 0 && argc != 4)
	{
		ft_putstr("Error: julia require 2 additional arguments\n");
		exit(0);
	}
	if (ft_strcmp(argv[1], "julia") == 0)
		check_julia_args(argv);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->l_len + x * (mlx->bpp / 8));
	*(unsigned int *) dst = color;
}

int	drawing(t_mlx *mlx)
{
	if (ft_strcmp(mlx->name, "mandelbrot") == 0)
		parse_m(*mlx);
	if (ft_strcmp(mlx->name, "julia") == 0)
		parse_j(*mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_mlx	mlx;

	(void) envp;
	(void) argc;
	check_args(argc, argv);
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, 600, 600, "fractol");
	mlx.img = mlx_new_image(mlx.mlx, 600, 600);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.l_len, &mlx.endian);
	mlx.name = argv[1];
	mlx.zoom = 1;
	mlx.max_iter = 20;
	if (ft_strcmp(mlx.name, "julia") == 0)
	{
		mlx.julia_x = get_julia_arg(argv[2]);
		mlx.julia_y = get_julia_arg(argv[3]);
	}
	get_color(&mlx);
	mlx_loop_hook(mlx.mlx, drawing, &mlx);
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, close_windows, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}
