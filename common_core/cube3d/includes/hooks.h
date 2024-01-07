/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:50:38 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/11 16:18:55 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "cub3d.h"

int	key_hook(int keycode, t_all *all);
int	hook_up(t_all *all);
int	hook_down(t_all *all);
int	hook_left(t_all *all);
int	hook_right(t_all *all);

int	exit_without_error(t_all *all);

#endif