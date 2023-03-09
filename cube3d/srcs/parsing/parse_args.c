/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:27:50 by jolivier          #+#    #+#             */
/*   Updated: 2023/03/02 16:44:36 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define BUFFER_SIZE 1

int	get_next_line(int fd, char **line)
{
	int		ret;
	char	*tmp;
	char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		if (buffer[0] == '\n')
			break ;
		tmp = *line;
		*line = ft_strjoin(*line, buffer);
		free(tmp);
		if (ft_strchr(*line, '\n'))
			break ;
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	if (ret < 0)
		return (-1);
	return (ret > 0 || ft_strlen(*line) > 0);
}

int	check_texture(t_map *map, char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		parse_texture(line, map, NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		parse_texture(line, map, SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		parse_texture(line, map, WEST);
	else if (line[0] == 'E' && line[1] == 'A')
		parse_texture(line, map, EAST);
	else if (line[0] == 'S' && line[1] == ' ')
		parse_texture(line, map, SPRITE);
	return (SUCCESS);
}

int	parse_args(char *argv, t_map *map)
{
	int		fd;
	char	*line;

	map->wall = malloc(sizeof(char *) * 5 + 1);
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error("Error\nCan't open file\n");
	while (get_next_line(fd, &line) == 1)
	{
		check_texture(map, line);
		if (line[0] == 'R')
			parse_resolution(line, map);
		else if (line[0] == 'F')
			parse_color(line, map, 0);
		else if (line[0] == 'C')
			parse_color(line, map, 1);
		else if (line[0] == '1' || line[0] == '0' || line[0] == '2')
			parse_map_line(line, map);
		else if (line[0] == '\0' && map->height != 0)
			error("Error Map");
		free(line);
	}
	free(line);
	close(fd);
	return (SUCCESS);
}
