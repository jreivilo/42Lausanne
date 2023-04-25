/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:01:22 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/13 13:29:11 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>

# include "structs.h"
# include "build.h"
# include "hooks.h"
# include "parsing.h"
# include "raycasting.h"

# define SUCCESS 0
# define ERROR 1

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4

# define NOTHING 99
# define BUFFER_SIZE 1

int		error(char *str);
void	error_with_free(t_map *map, char *str);

#endif