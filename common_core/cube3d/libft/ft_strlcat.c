/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:25:22 by jolivier          #+#    #+#             */
/*   Updated: 2022/07/18 20:25:24 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	s_dest;

	j = 0;
	i = 0;
	s_dest = ft_strlen(dest);
	while (dest[i] != '\0')
	{
		i++;
	}
	while (src[j] != '\0' && i + 1 < size)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	if (size >= s_dest)
		return (s_dest + ft_strlen(src));
	else
		return ((ft_strlen(src) + size));
}
