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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start + len > ft_strlen((char *)s))
		len = ft_strlen((char *)s) - start;
	if (start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read_file(int fd, char *buff, int *size, char **line)
{
	char	*tmp;

	while (*size > 0)
	{
		buff[*size] = '\0';
		if (*line == NULL)
			*line = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(*line, buff);
			free(*line);
			*line = tmp;
		}
		if (ft_strchr(*line, '\n'))
			break ;
		*size = read(fd, buff, BUFFER_SIZE);
	}
	return (*line);
}

int	ft_check_next_stop(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		return (++i);
	return (i);
}

char	*ft_check_line(char **line)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = ft_check_next_stop(*line);
	tmp = ft_substr(*line, 0, i);
	tmp2 = ft_substr(*line, i, ft_strlen(*line) - i + 1);
	free(*line);
	*line = tmp2;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		buff [BUFFER_SIZE + 1];
	int			size;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	size = read(fd, buff, BUFFER_SIZE);
	if (size <= 0 && line == NULL)
		return (NULL);
	ft_read_file(fd, buff, &size, &line);
	if (*line || size > 0)
		return (ft_check_line(&line));
	free(line);
	return (NULL);
}
