/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:59:24 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/13 13:34:09 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "cub3d.h"

int		get_next_line(int fd, char **line);
int		parse_args(char *argv, t_map *map);
int		parse_map_line(char *line, char *tmp);
int		realloc_map(t_map *map, char *line);
int		true_len(char *line);

int		parse_color(char *line, t_map *map, int i);
int		parse_texture(char *line, t_map *map, int i);
int		parse_resolution(char *line, t_map *map);
int		parse_player(t_map *map, t_player *player);

int		check_map(t_map *map);
int		check_map_border(t_map *map);
int		check_name_map(char *argv);
void	add_protect(t_map *map);

int		is_not_map(t_map *map);
char	*ft_trim(char *line);
int		ft_isspace(int c);

void	parse_color_iteration(char *line, int *j);
void	parse_color_init_color_floor(t_map *map, int r, int g, int b);
void	parse_color_init_color_ceiling(t_map *map, int r, int g, int b);

void	check_map_border_corner(t_map *map, int i, int j);
void	check_map_border_first_and_last_row(t_map *map, int i, int j);
void	check_map_border_first_and_last(t_map *map, int i, int j);

#endif