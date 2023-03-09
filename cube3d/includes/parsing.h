/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:59:24 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 15:50:17 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

int	get_next_line(int fd, char **line);
int	parse_args(char *argv, t_map *map);
int	parse_map_line(char *line, t_map *map);

int	parse_color(char *line, t_map *map, int i);
int	parse_texture(char *line, t_map *map, int i);
int	parse_resolution(char *line, t_map *map);
int	parse_player(t_map *map, t_player *player);

int	check_map(t_map *map);
#endif