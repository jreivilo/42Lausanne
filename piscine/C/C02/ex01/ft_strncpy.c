/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 11:42:46 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/17 11:43:12 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	int	i;
	int	j;

	i = 0;
	j = n;
	while (src[i] != '\0' && i < j)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < j)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

/*
int main(void)
{
	char a[20] = "";
	char b[20] = "test";
	ft_strncpy(a, b, 2);
	printf("%s\n", ft_strncpy(a, b, 2));
	printf("%s\n", ft_strncpy(a, b, 10));
}
*/
/*
The stpncpy() and strncpy() functions copy at most len characters from
src into dst.  If src is less than len characters long, the remainder of
dst is filled with `\0' characters.  Otherwise, dst is not terminated.
*/