/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 20:10:28 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/25 20:10:30 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*ft_strdup(char *src)
{
	int		i;
	int		size;
	char	*dest;

	i = 0;
	size = 0;
	while (src[size] != '\0')
	{
		size++;
	}
	dest = malloc(sizeof(char) * (size + 1));
	if (dest != (void *)0)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}
/*
int main()
{
	char *c = "Hello";
	write(1, ft_strdup(c), 1);
	printf("R:%s", ft_strdup(c));
	return(0);


}
*/