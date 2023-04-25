/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nadel-be <nadel-be@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 14:27:50 by jolivier          #+#    #+#             */
/*   Updated: 2023/04/17 12:37:35 by nadel-be         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	else
		free(line);
	return (SUCCESS);
}

int	check_color(t_map *map, char *line)
{
	if (line[0] == 'F')
		parse_color(line, map, 0);
	else if (line[0] == 'C')
		parse_color(line, map, 1);
	free(line);
	return (SUCCESS);
}

int	check_global(t_map *map, char *line)
{
	char	*tmp;

	if (ft_strlen(line) == 0)
		return (SUCCESS);
	if (is_not_map(map) == 0)
	{
		tmp = ft_calloc(sizeof(char), true_len(line) + 1);
		if (!(tmp))
			error("Malloc error");
		parse_map_line(line, tmp);
		map->map_set = 1;
		realloc_map(map, tmp);
		return (SUCCESS);
	}
	line = ft_trim(line);
	if (ft_strncmp(line, "R ", 2) == 0)
		parse_resolution(line, map);
	else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		check_color(map, line);
	else
		check_texture(map, line);
	return (SUCCESS);
}

int	parse_args(char *argv, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error("Error\nCan't open file\n");
	while (get_next_line(fd, &line) == 1)
	{
		if (ft_strlen(line) == 0 && map->map_set == 1)
		{
			error("Map error: cut\n");
			break ;
		}
		check_global(map, line);
		free(line);
	}
	free(line);
	close(fd);
	return (SUCCESS);
}
