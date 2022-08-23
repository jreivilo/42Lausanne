/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 19:55:26 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 19:55:27 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <string.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	i = 0;
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && j < nb)
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
	char a[20] = "42dfgdl33r ";
	char b[20] = " l33r";
	printf("%s\n", a);
	printf("%s\n", ft_strncat(a, b, 2));

	char c[20] = "42dfgdl33r ";
	char d[20] = " l33r";
	printf("%s\n", c);
	printf("%s\n", strncat(c, d, 2));
}
*/
/*
dest − This is pointer to the destination array, which should contain a 
C string, and should be large enough to contain the concatenated 
resulting string which 
includes the additional null-character.
src − This is the string to be appended.
n − This is the maximum number of characters to be appended.
*/