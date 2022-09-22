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

char *get_next_line(int fd)
{
	char temp[BUFFER_SIZE + 1];
	char *line;
	char *fline;
	int size;
	int i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 0;
	size = 1;
	line = (char *)malloc(sizeof(char));
	if (line == NULL)
		return (NULL);

	while (size > 0)
	{
		size = read(fd, &temp, BUFFER_SIZE);
		if (size == -1)
			return (NULL);
		temp[size] = '\0';
		//printf("size = %d\n", size);
		i = 0;
		while(i < size)
		{
			if(temp[i] == '\n')
			{
				temp[i - 1] = '\0';
				line = ft_strjoin(line, temp);
				fline = ft_strdup(line);
				return (fline);
			}
			i++;
		}
		line = ft_strjoin(line, temp);
	}
	fline = ft_strdup(line);
	return (fline);
}

// int main(int argc, char **argv)
// {
// 	int fd;
// 	char *line;

// 	fd = open(argv[1], O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("R:%s\n", line);
// 	return (0);
// }

