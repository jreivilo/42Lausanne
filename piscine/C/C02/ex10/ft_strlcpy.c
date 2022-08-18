/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 17:34:47 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 17:34:49 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)

{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dest[i] = '\0';
		i++;
	}
	return (ft_len(src));
}
/*
int main(void)
{
	char a[20] = "erfwewr";
	char b[20] = "fsd";
	printf("%u\n", ft_strlcpy(a, b, 10));
	printf("%s\n", a);
	printf("%ld\n", strlcpy(a, b, 10));
	printf("%s\n", a);
}
*/
/*
strlcpy() copies up to dstsize - 1 characters from the string 
src to dst, NUL-terminating the
result if dstsize is not 0.
*/