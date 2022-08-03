/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 18:52:28 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 18:52:30 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
int main(void)
{
	char a[50] = "Ouioui";
	char b[50] = "Teletobies";
	printf("%s\n", a);
	ft_strcat(a, b);
	printf("%s\n", a);
	char c[50] = "Ouioui";
	char d[50] = "Teletobies";
	printf("%s\n", c);
	strcat(c, d);
	printf("%s\n", c);
}
*/