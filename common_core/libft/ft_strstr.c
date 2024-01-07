/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jolivier <jolivier@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 10:24:12 by jolivier          #+#    #+#             */
/*   Updated: 2022/09/05 10:24:12 by jolivier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (needle[0] == '\0')
	{
		return ((char *)haystack);
	}
	while (haystack[i] != '\0')
	{
		while (haystack[i + n] == needle[n])
		{
			if (needle[n + 1] == '\0')
			{
				return ((char *)haystack + i);
			}
		n++;
		}
		n = 0;
		i++;
	}
	return ((void *)0);
}
