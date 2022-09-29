/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:20:02 by jolivier          #+#    #+#             */
/*   Updated: 2022/09/18 15:20:02 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

// *char	get_line(int fd, )
// {
// 	int size;
// 	char temp[BUFFER_SIZE + 1];
// 	char *line;

// 	line = malloc(sizeof(char) * 1);
// 	size = read(fd, &temp, BUFFER_SIZE);
// 	if (size == -1)
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	temp[size] = '\0';
// 	if (size == 0)
// 	{
// 		fline = ft_strdup(line);
// 		free(line);
// 		return (fline);
// 	}
// }

char	*get_next_line(int fd)
{
	char	temp[BUFFER_SIZE + 1];
	char	*line;
	char	*fline;
	int		size;
	int		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	size = 1;
	line = malloc(sizeof(char) * 1);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	while (size > 0)
	{
		size = read(fd, &temp, BUFFER_SIZE);
		if (size == -1)
		{
			free(line);
			return (NULL);
		}
		temp[size] = '\0';
		i = 0;
		while (i < size)
		{
			if (temp[i] == 13)
			{
				temp[i] = '\0';
				line = ft_strjoin(line, temp);
				fline = ft_strdup(line);
				free(line);
				return (fline);
			}
			i++;
		}
		line = ft_strjoin(line, temp);
	}
	fline = ft_strdup(line);
	free(line);
	return (fline);
}
/*
char *get_next_line(int fd)
{
	char *buffer;
	int size;
	int	i;
	int j;
	char *final;
	char *f_final;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	final = (char *)malloc(sizeof(char));
	j = 0;
	size = 1;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
	{
		free(final);
		free(buffer);
		return (NULL);
	}
	while (size > 0)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1)
		{
			free(final);
			free(buffer);
			return (NULL);
		}
		if (size == 0)
		{
			final[j] = '\0';
			f_final = ft_strdup(final);
			free(final);
			free(buffer);
			return(f_final);
		}
		buffer[size] = '\0';
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
		{
			final[i + j] = buffer[i];
			i++;
		}
		j = j + i;
		if (buffer[i] == '\n')
		{
			final[j - 1] = '\0';
			f_final = ft_strdup(final);
			free(final);
			free(buffer);
			return(f_final);
		}
	}
	f_final = ft_strdup(final);
	free(final);
	free(buffer);
	return(f_final);
}

int main(int argc, char **argv)
{
	int fd;
	char *line;

	argc = 2;
	argc = argc + 1;
	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("Result:%s\n", line);
	return (0);
}
*/