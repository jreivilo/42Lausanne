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
	char *temp;
	char *line;
	int count;
	int size;
	int i;

	count = 0;
	size = 1;

	while (size > 0 && temp[count + i] != '\0')
	{
		i = 0;
		size = read(fd, &temp[count], BUFFER_SIZE);
		count = count + size;

		while (temp[count + i] != '\n' && temp[count + i] != '\0')
		{
			i++;
		}
		if (temp[count + i] == '\n')
		{
			temp[count + i] == '\0';
			printf("OUT");
			break;
		}
	}
	//line = ft_strdup(temp);
	return (temp);
}


int main(int argc, char **argv)
{
	int fd;
	char *line;

	fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("L:%s\n", line);
	return (0);
}
