/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 14:51:52 by jolivier          #+#    #+#             */
/*   Updated: 2022/12/01 17:16:59 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <stdio.h>

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	char	*name;
	int		bpp;
	int		l_len;
	int		endian;
	double	julia_x;
	double	julia_y;
	double	zoom;
	double	x;
	double	y;
	int		max_iter;
	int		co[10];
}	t_mlx;

typedef struct s_frac
{
	double	x0;
	double	y0;
	double	xtemp;
	double	x;
	double	y;
}	t_frac;

typedef struct s_atoi_double
{
	double	j_arg;
	int		len_total;
	int		len_dot;
	int		diff;
	int		i;
	int		j;
}	t_atoi_double;

void	ft_putchar(char c);
void	ft_putstr(char *str);

int		ft_strlen(char *str);
int		ft_strlen_dot(char *str);
void	get_variable_value(t_atoi_double *atoi_d, char *argv);
int		get_julia_arg_before_point(t_atoi_double *atoi_d, char *argv);
double	get_julia_arg(char *argv);

void	get_color(t_mlx	*mlx);
void	mandelbrot(int cor_x, int cor_y, t_mlx mlx);
void	julia(int cor_x, int cor_y, t_mlx mlx);

int		mouse_hook(int button, int x, int y, t_mlx *mlx);
int		close_windows(t_mlx *mlx);
int		key_hook(int keycode, t_mlx *mlx);

int		ft_strcmp(char *s1, char *s2);
void	parse_j(t_mlx mlx);
void	parse_m(t_mlx mlx);
void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

int		drawing(t_mlx *mlx);

void	parse_m(t_mlx mlx);
void	parse_j(t_mlx mlx);

void	check_julia_args(char **argv);
void	check_number(char *str);
int		norminette(char *str);

#endif