/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 15:19:31 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 15:49:23 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_H
# define BUILD_H

# include "cub3d.h"

int	build_game(t_map *map, t_player *player);

int	pixel_put(t_game *game, int x, int y, int color);

#endif